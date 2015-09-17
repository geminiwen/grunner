#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/fcntl.h>

int main() {
    int a,b;

    int aa = open("/Users/geminiwen/Code/CLionProjects/grunner/test/test.sample2", O_CREAT);
    int ab = open("/tmp/test.txt", O_RDONLY);
    printf("aa:%d\n", aa);
    printf("ab:%d\n", ab);
    return 0;
}