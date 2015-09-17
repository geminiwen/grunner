#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int a,b;
    scanf("%d%d", &a, &b);
    printf("%d\n", a+b);
    perror("test");
    return 0;
}