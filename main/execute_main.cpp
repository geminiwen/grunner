#include <iostream>
#include <unistd.h>
#include "../deps/run.h"

using namespace std;

int main(int args, char* argv[]) {
    Process process = {0};
    Result result = {0};
    init_run(&process);

    int pid = fork();
    if (pid == 0) {
        run_it(&process);
    } else if (pid > 0) {
        resolve(pid, &process, &result);
    }
    return 0;
}

