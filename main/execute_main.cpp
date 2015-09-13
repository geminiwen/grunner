#include <iostream>
#include <unistd.h>
#include <sys/fcntl.h>
#include "../deps/run.h"

using namespace std;

int main(int args, char* argv[]) {
    Process process = {0};
    Result result = {0};
    init_run(&process);

    process.path = "/Users/geminiwen/Code/CLionProjects/grunner/test/test";
    process.time_limit = 1000;
    process.memory_limit = 1024 * 64;
    process.fin = open("/Users/geminiwen/Code/CLionProjects/grunner/test/test.in", O_RDONLY);
    process.fout = open("/Users/geminiwen/Code/CLionProjects/grunner/test/test.out", O_WRONLY | O_CREAT);
    process.uid = getuid();

    int pid = fork();
    if (pid == 0) {
        run_it(&process);
    } else if (pid > 0) {
        resolve(pid, &process, &result);
        printf("%d\n", result.memory_used);
    }
    return 0;
}

