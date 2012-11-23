#include <stdio.h>
#include <stdlib.h>

#define NUM_PAGES (1024 * 64)
#define PAGE_SIZE 4096
static unsigned char buf[NUM_PAGES][PAGE_SIZE]; 
static unsigned long long round; 
 
inline write_mem(long start, long range)
{
    round++;
    unsigned long y = start + (round * random() % range);
    buf[y % NUM_PAGES][random() % PAGE_SIZE]++;
}

int main()
{
    while (1) {
        write_mem(10000, 100);
        write_mem(1000, 1000);
        write_mem(100, 10000);
        if (! (round % NUM_PAGES)) {
            fprintf(stderr, ".");
            usleep(1000);
        }
   }
}

