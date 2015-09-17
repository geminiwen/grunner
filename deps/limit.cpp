//
// Created by 温盛章 on 15/9/9.
//

#include <sys/resource.h>
#include <stdio.h>
#include <sys/errno.h>
#include <unistd.h>
#include "limit.h"

void set_process_limit(Process *process) {
    struct rlimit rl;
    /*struct itimerval p_realt;*/

    //TODO set time limit test value is 2s
    rl.rlim_cur = process->time_limit / 1000 + 1;
    if (process->time_limit % 1000 > 800) {
        rl.rlim_cur += 1;
    }
    rl.rlim_max = rl.rlim_cur + 1;

    //设置CPU时间
    if (setrlimit(RLIMIT_CPU, &rl))
        printf("set RLIMIT_CPU failure");

    rl.rlim_cur = process->memory_limit * 1024;
    rl.rlim_max = rl.rlim_cur + 1024;
    if (setrlimit(RLIMIT_DATA, &rl))
        printf("set RLIMIT_DATA failure");

    rl.rlim_cur = 16 * 1024 * 1024;
    rl.rlim_max = rl.rlim_cur + 1024;
    if (setrlimit(RLIMIT_STACK, &rl))
        printf("set RLIMIT_STACK failure, error no:%d\n", errno);

    rl.rlim_cur = 0;
    rl.rlim_max = 0;
    if (setrlimit(RLIMIT_NPROC, &rl)) {
        printf("set RLIMIT_NPROC failure, error no:%d\n", errno);
    }

    rl.rlim_cur = 2;
    rl.rlim_max = 2;
    if (setrlimit(RLIMIT_FSIZE, &rl)) {
        printf("set RLIMIT_FSIZE failure, error no:%d\n", errno);
    }

    // 设置警报
    uint32_t time_limit = (uint32_t) (process->time_limit / 1000) + 1;
    alarm(time_limit);
}