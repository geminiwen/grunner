#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    while(1) {
        int p = fork();
        printf("%d\n", p);
        fflush(stdout);
        sleep(1);
    }
    return 0;
}