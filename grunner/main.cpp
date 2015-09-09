#include <iostream>
#include <unistd.h>

#include "debug.h"
#include "run.h"
#include "limit.h"

using namespace std;

int main(int args, char* argv[]) {
    Process process = {0};
    Result result = {0};
    init_run(&process);

    int pid = vfork();
    if (pid == 0) {
        run_it(&process);
    } else if (pid > 0) {
        resolve(pid, &process, &result);
    }
    return 0;
}

/**
 * 初始化进程参数
 *
 * TODO 解析输入
 */
void init_run(Process *process) {
    process->time_limit = 2000;
    process->memory_limit = 64 * 1024;
    process->path = "/Users/geminiwen/Code/ClionProjects/grunner/test/test.out";
}

/**
 * 设置进程资源限制，运行进程
 */
void run_it(Process *process) {
    set_process_limit(process);

    //TODO 重定向输入输出流
    execv(process->path, NULL);
}


/**
 * 解析结果
 */
void resolve(int pid, Process *process, Result *rst) {
    int status;
    struct rusage ru;
    //等待一个信号
    wait4(pid, &status, WSTOPPED, &ru);

    rst->time_used = ru.ru_utime.tv_sec * 1000 + ru.ru_utime.tv_usec / 1000;
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
        else if (rst->memory_used > process->memory_limit)
            rst->judge_result = MLE;
        else
            rst->judge_result = AC;
    }

}