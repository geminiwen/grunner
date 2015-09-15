//
// Created by Gemini Wen on 15/9/12.
//

#include <node.h>
#include "../deps/run.h"
#include "../deps/check.h"


namespace grunner {

    using v8::Exception;
    using v8::FunctionCallbackInfo;
    using v8::HandleScope;
    using v8::Isolate;
    using v8::Local;
    using v8::Object;
    using v8::String;
    using v8::Value;
    using v8::Context;
    using v8::Number;
    using v8::Function;
    using v8::Null;

    void run(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();
        Local<Context> context = Context::New(isolate);

        if (args.Length() < 2) {
            isolate->ThrowException(Exception::TypeError(
                    String::NewFromUtf8(isolate, "Wrong arugments")
            ));
            return;
        }

        Local<Object> processProps = args[0]->ToObject();
        Local<Function> callback = Local<Function>::Cast(args[1]);

        Local<Value> path;
        processProps->Get(context, String::NewFromUtf8(isolate, "path")).ToLocal(&path);

        Local<Value> fin;
        processProps->Get(context, String::NewFromUtf8(isolate, "fin"))
                     .ToLocal(&fin);

        Local<Value> fout;
        processProps->Get(context, String::NewFromUtf8(isolate, "fout"))
                .ToLocal(&fout);

        Local<Value> uid;
        processProps->Get(context, String::NewFromUtf8(isolate, "uid"))
                .ToLocal(&uid);

        Local<Value> timeLimit;
        processProps->Get(context, String::NewFromUtf8(isolate, "timeLimit"))
                .ToLocal(&timeLimit);

        Local<Value> memoryLimit;
        processProps->Get(context, String::NewFromUtf8(isolate, "memoryLimit"))
                .ToLocal(&memoryLimit);

        Process process = {0};
        Result result = {0};

        init_run(&process);

        if (!path.IsEmpty()) {
            process.path = *String::Utf8Value(path->ToString());
        }

        if (!fin.IsEmpty()) {
            process.fin = fin->Int32Value();
        }

        if (!fout.IsEmpty()) {
            process.fout = fout->Int32Value();
        }

        if (!uid.IsEmpty()) {
            process.uid = uid->Uint32Value();
        }

        if (!timeLimit.IsEmpty()) {
            process.time_limit = timeLimit->Uint32Value();
        }

        if (!memoryLimit.IsEmpty()) {
            process.memory_limit = memoryLimit->Uint32Value();
        }

        int pid = vfork();
        if (pid == 0) {
            run_it(&process);
        } else if (pid > 0) {
            resolve(pid, &process, &result);
            Local<Object> obj = Object::New(isolate);
            obj->Set(String::NewFromUtf8(isolate, "judgeResult"), Number::New(isolate, result.judge_result));
            obj->Set(String::NewFromUtf8(isolate, "timeUsed"), Number::New(isolate, result.time_used));
            obj->Set(String::NewFromUtf8(isolate, "memoryUsed"), Number::New(isolate, result.memory_used));
            const unsigned argc = 1;
            Local<Value> argv[argc] = { obj };
            callback->Call(Null(isolate), argc, argv);
        }
    }

    void check(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();

        if (args.Length() < 2) {
            isolate->ThrowException(Exception::TypeError(
                    String::NewFromUtf8(isolate, "Wrong arugments")
            ));
            return;
        }

        int sampleIn;
        int userIn;
        int result;

        sampleIn =  args[0]->Int32Value();
        userIn = args[1]->Int32Value();

        checkDiff(sampleIn, userIn, &result);
        args.GetReturnValue().Set(Number::New(isolate, result));
    }

    void init (Local<Object> exports) {
        NODE_SET_METHOD(exports, "run", run);
        NODE_SET_METHOD(exports, "check", check);
    }

    NODE_MODULE(grunner, init)
}