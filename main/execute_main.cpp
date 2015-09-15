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

    process.path = "java";
    process.time_limit = 1000;
    process.memory_limit = 1024 * 64;
    process.fin = open("/Users/geminiwen/Code/CLionProjects/grunner/test/test.in", O_RDONLY);
    process.fout = open("/Users/geminiwen/Code/CLionProjects/grunner/test/test.out", O_WRONLY | O_CREAT);
    process.uid = getuid();

    int length = 4;
    char** tmp =  (char**)malloc(sizeof(char*) *(length + 1));
    tmp[0] = "java";
    tmp[1] = "-classpath";
    tmp[2] = "/Users/geminiwen/Code/IdeaProjects/gemini-oj-web/tmp/144230884855f7e2f037ea6";
    tmp[3] = "Judge";
    tmp[4] = NULL;
    process.args = (char * const *)tmp;

    int pid = vfork();
    if (pid == 0) {
        run_it(&process);
        free(tmp);
    } else if (pid > 0) {

        resolve(pid, &process, &result);

        int user_out = open("/Users/geminiwen/Code/CLionProjects/grunner/test/test.out", O_RDONLY);
        int sample_out = open("/Users/geminiwen/Code/CLionProjects/grunner/test/sample.out", O_RDONLY);

        int solved_result;
        checkDiff(sample_out, user_out, &solved_result);
        printf("result: %d\n", solved_result);
    }
    return 0;
}

