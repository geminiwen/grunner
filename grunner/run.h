//
// Created by 温盛章 on 15/9/9.
//

#ifndef GRUNNER_RUN_H
#define GRUNNER_RUN_H
typedef struct {
    char* path;
    char* const* args;
    int fin;
    int fout;
    uid_t uid;
    rlim_t time_limit;     //in million seconds
    rlim_t memory_limit;   //in kilo byte
} Process;

typedef struct {
    long judge_result;
    long time_used;
    long memory_used;
} Result;

enum JUDGE_RESULT{
    AC = 0,
    PE,	    //1 Presentation Error
    TLE,	//2 Time Limit Exceeded
    MLE,	//3 Memory Limit Exceeded
    WA,	    //4 Wrong Answer
    RE,	    //5 Runtime Error
    OLE,	//6 Output Limit Exceeded
    CE,	    //7 Compile Error
    SE,     //8 System Error
};


void init_run(Process *process);
void run_it(Process *process);
void resolve(int pid, Process *process, Result *rst);

#endif //GRUNNER_RUN_H
