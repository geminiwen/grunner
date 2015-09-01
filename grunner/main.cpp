#include <iostream>
#include <unistd.h>

#include "debug.h"
using namespace std;

int main() {
    int fd_err[2];
    int pid = vfork();
    if(pipe(fd_err)) {
        DEBUG("pipe error");
    }
    if (pid == 0) {
        printf("%d %d\n", fd_err[0], fd_err[1]);
        close(fd_err[0]);
        DEBUG("in child process");
    } else if (pid > 0) {
        printf("%d %d\n", fd_err[0], fd_err[1]);
        DEBUG("in parent process");
    }
    return 0;
}