#include <iostream>
#include <unistd.h>
#include <sys/fcntl.h>
#include "../deps/run.h"
#include "../deps/check.h"

using namespace std;

int main(int args, char* argv[]) {
    Process process = {0};
    Result result = {0};
    init_run(&process);

    process.path = "/Users/geminiwen/Code/CLionProjects/grunner/test/test";
    process.time_limit = 10000;
    process.memory_limit = 1024 * 64;
    process.fin = open("/Users/geminiwen/Code/CLionProjects/grunner/test/test.in", O_RDONLY);
    process.fout = open("/Users/geminiwen/Code/CLionProjects/grunner/test/test.out", O_WRONLY | O_CREAT);
    process.uid = getuid();

    int pid = vfork();
    if (pid == 0) {
        run_it(&process);
    } else if (pid > 0) {

        resolve(pid, &process, &result);

        int user_out = open("/Users/geminiwen/Code/CLionProjects/grunner/test/test.out", O_RDONLY);
        int sample_out = open("/Users/geminiwen/Code/CLionProjects/grunner/test/sample.out", O_RDONLY);

        int solved_result;
        checkDiff(sample_out, user_out, &solved_result);
    }
    return 0;
}

