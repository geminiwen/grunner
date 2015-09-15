//
// Created by Gemini Wen on 15/9/12.
//

#include "run.h"
#include <iostream>
#include <sys/fcntl.h>
#include "debug.h"
#include "limit.h"


/**
 * 初始化进程参数
 *
 */
void init_run(Process *process) {

    process->fin = -1;
    process->fout = -1;
    process->uid = 0;
    process->path = NULL;
    process->args = NULL;

    process->time_limit = 1000;
    process->memory_limit = 64 * 1024;


}

/**
 * 设置进程资源限制，运行进程
 */
void run_it(Process *process) {

    if (process->fin != -1) {
        dup2(process->fin, STDIN_FILENO);
    }

    if (process->fout != -1) {
        dup2(process->fout, STDOUT_FILENO);
    }

    setuid(process->uid);

    if (process->path != NULL) {
        set_process_limit(process);
        int rl = execvp(process->path, process->args);
        if (rl) {
            perror("error");
        }
    }
}


/**
 * 解析运行结果
 */
void resolve(int pid, Process *process, Result *rst) {
    int status;
    struct rusage ru;
    //等待一个信号
    wait4(pid, &status, WSTOPPED, &ru);

    rst->time_used = ru.ru_utime.tv_sec * 1000 + ru.ru_utime.tv_usec / 1000
                     + ru.ru_stime.tv_sec * 1000 + ru.ru_stime.tv_usec / 1000;
    rst->memory_used = ru.ru_minflt * (sysconf(_SC_PAGESIZE) / 1024);

    if (WIFSIGNALED(status)) {
        switch (WTERMSIG(status)) {
            case SIGSEGV:
                if (rst->memory_used > process->memory_limit)
                    rst->judge_result = MLE;
                else
                    rst->judge_result = RE;
                break;
            case SIGALRM:
            case SIGXCPU:
                rst->time_used = (long) process->time_limit;
                rst->judge_result = TLE;
                break;
            default:
                rst->judge_result = RE;
                break;
        }
        DEBUG("sig:%d\n" , WTERMSIG(status));
        DEBUG("result: %d\n", rst->judge_result);
    } else {
        if (rst->time_used > process->time_limit)
            rst->judge_result = TLE;
        else if (rst->memory_used > process->memory_limit) {
            rst->judge_result = MLE;
        } else {
            rst->judge_result = AC;
        }
    }
}