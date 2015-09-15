#include <stdio.h>
#include <stdlib.h>

int main() {
    int a,b;
    char *p = (char *)malloc(65636*1024*1024);
    while(~scanf("%d%d",&a,&b)) {
        printf("%d\n", a+b);
    }
    free(p);
    return 0;
}