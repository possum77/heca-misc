#include <stdlib.h>
#include <stdio.h>
int main()
{
    char *buf = (char *) calloc(4096, 4096);
    while (1) {
        int i;
        for (i = 0; i < 4096 * 4; i++) {
            buf[i * 4096 / 4]++;
        }
        printf(".");
    }
}

