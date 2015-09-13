//
// Created by Gemini Wen on 15/9/12.
//

#include <node.h>
#include "../deps/run.h"


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

    void run(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();
        Local<Context> context = Context::New(isolate);

        if (args.Length() < 1) {
            isolate->ThrowException(Exception::TypeError(
                    String::NewFromUtf8(isolate, "Wrong arugments")
            ));
            return;
        }

        Local<Object> processProps = args[0]->ToObject();

        Local<Value> path;
        processProps->Get(context, String::NewFromUtf8(isolate, "path")).ToLocal(&path);

        printf("what:%s\n", *String::Utf8Value(path->ToString()));

//        Local<Value> fin;
//        processProps->Get(context, String::NewFromUtf8(isolate, "fin"))
//                     .ToLocal(&fin);
//
//        Local<Value> fout;
//        processProps->Get(context, String::NewFromUtf8(isolate, "fout"))
//                .ToLocal(&fout);
//
//        Local<Value> uid;
//        processProps->Get(context, String::NewFromUtf8(isolate, "uid"))
//                .ToLocal(&uid);
//
//        Local<Value> timeLimit;
//        processProps->Get(context, String::NewFromUtf8(isolate, "timeLimit"))
//                .ToLocal(&timeLimit);
//
//        Local<Value> memoryLimit;
//        processProps->Get(context, String::NewFromUtf8(isolate, "memoryLimit"))
//                .ToLocal(&memoryLimit);
//
//        Process process = {0};
//        Result result = {0};
//
//        init_run(&process);
//
//        if (!path.IsEmpty()) {
//            process.path = *String::Utf8Value(path->ToString());
//        }
//
//        if (!fin.IsEmpty()) {
//            process.fin = fin->Int32Value();
//        }
//
//        if (!fout.IsEmpty()) {
//            process.fout = fout->Int32Value();
//        }
//
//        if (!uid.IsEmpty()) {
//            process.uid = uid->Uint32Value();
//        }
//
//        if (!timeLimit.IsEmpty()) {
//            process.time_limit = timeLimit->Uint32Value();
//        }
//
//        if (!memoryLimit.IsEmpty()) {
//            process.memory_limit = memoryLimit->Uint32Value();
//        }
//
//        int pid = vfork();
//        if (pid == 0) {
//            run_it(&process);
//        } else if (pid > 0) {
//            resolve(pid, &process, &result);
//            int judgeResult = result.judge_result;
//            args.GetReturnValue().Set(judgeResult);
//        }
    }

    void init (Local<Object> exports) {
        NODE_SET_METHOD(exports, "run", run);
    }

    NODE_MODULE(grunner, init)
}