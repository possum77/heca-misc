#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/types.h>
#include <string.h>

#define PAGE 4096

#define KB * 1024UL
#define MB * 1048576UL
#define GB * 1073741824UL

#define NSEC * 1UL
#define USEC * 1000UL
#define MSEC * 1000000UL
#define SEC  * 1000000000UL

#define u8 u_int8_t
#define u32 u_int32_t
#define u64 u_int64_t
#define u128 u_int64_t

static u64 rand_u64(u64 curr)
{
	return (curr + 104729) * 98849;
}

u128 nsec_diff(struct timespec start, struct timespec end)
{
    struct timespec temp;
    u128 ret;

    temp.tv_sec = end.tv_sec - start.tv_sec;
    temp.tv_nsec = end.tv_nsec - start.tv_nsec;

    ret = temp.tv_sec;
    ret *= (1 SEC);
    ret += temp.tv_nsec;

    return ret;
}

struct worker {
    struct worker *next;
    pthread_t task;

    char name[10];
    u8 *addr;
    u64 offset;
    u64 len;
    u64 bw;

    u64 current;
    u64 bytes;
    u64 seq;
};

static struct worker *head;
u8 write_char;
struct timespec prev;
struct timespec start = {0, 0};

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define PAGE_SEQ 11

void *task(void *arg)
{
    struct worker *work = (struct worker *) arg;

    for (;;) {
        struct timespec curr;
        u64 size = 17;
        u8 *addr, c;
        long double effort, secs;
	int i;

        effort = work->bytes;
        effort /= work->bw;

        clock_gettime(CLOCK_REALTIME, &curr);
        secs = nsec_diff(prev, curr);
        secs /= 1 SEC;

        if (effort/secs > 1.5) {
	    usleep(10);
            continue; /* slow down */
        }

	work->seq = rand_u64(work->seq) % PAGE_SEQ;
        work->current = rand_u64(work->current) % work->len;
	for (i = 0; i < work->seq; i++) {
	    addr = work->addr + work->offset + work->current;
	    c = work->current & 0xff;
	    memset(addr, size, c);
            work->current = (work->current + PAGE) % work->len;
	}
	work->bytes += PAGE * work->seq;
    }
    return NULL;
}

int create_worker(const char *name, u8 *addr, u64 offset, u64 len, u64 bw)
{
    int ret;
    struct worker *new;

    new = calloc(1, sizeof(struct worker));
    assert(new);

    memcpy(new->name, name, MIN(strlen(name), sizeof (new->name)-1));
    new->addr = addr;
    new->offset = offset;
    new->len = len;
    new->bw = bw;

    new->next = head;
    head = new;

    ret = pthread_create(&new->task, NULL, task, new);
    assert(!ret);
    return 0;
}

static double eval_work(u64 interval)
{
    int rc = 0;
    struct worker *w;
    long double total_bytes = 0, total_bw = 0, ratio;

    for (w = head; w; w = w->next) {
        total_bytes += w->bytes;
        w->bytes = 0;
        total_bw += w->bw;
    }
    ratio = 1 SEC / interval;
    ratio *= total_bytes / total_bw;
    return MIN(ratio, 1.0);
}

static int arg_u64(char *s, const char *k, u64 *val)
{
    char key[256] = {0};
    int kn = strlen(k);

    if (strncmp(s, k, kn))
        return -1;
    if (strncmp(s + kn, "=", 1))
        return -1;
    *val = atol(s + kn + 1);
    return 0;

}

static void print_marker(u64 nsec, double eval)
{
    u64 sec = nsec / (1 SEC);
    nsec = nsec % (1 SEC);
    fprintf(stderr, "%03llu.%02llu %03.2f\n", sec, nsec / (10 MSEC), 100.0 * eval);
}

int main(int argc, char **argv)
{
    char *buf, *proc = argv[0];
    u64 memory = 512 MB, bandwidth = 1 GB, threads = 8, offset = 0, reminder = 0;
    int i;

    for (i = 1; i < argc; i++) {
        char *arg = argv[i];

        if (!*arg)
            break;
        if (*arg != '-')
            break;
        if (!arg_u64(arg, "-m", &memory))
            continue;
        if (!arg_u64(arg, "-b", &bandwidth))
            continue;
        if (!arg_u64(arg, "-t", &threads))
            continue;
        if (!strcmp(arg, "-")) {
            i++;
            break;
        }
    }

    if (i != argc) {
        fprintf(stderr, "usage: %s -m=<memory> -b=<bandwidth> -t=<threads>\n",
                proc);
        exit(1);
    }

#if AMB_DEBUG
    fprintf(stderr, "Arguments: memory=%llu, bandwidth=%llu, threads=%llu\n",
            memory, bandwidth, threads);
#endif

    buf = malloc(memory);
    assert(buf);

    for (i = 0; i < threads; i++) {
        char name[10] = {'a'+i, 0};
        u64 bw = bandwidth >> (threads - i);
        u64 len = memory >> (i+1);
        offset = rand_u64(offset) % (memory - len);

#if AMB_DEBUG
        fprintf(stderr, "Thread %s: offset=%llu, len=%llu, bw=%llu BPS\n",
                name, offset, len, bw);
#endif

        create_worker(name, buf, offset, len, bw);
    }

    clock_gettime(CLOCK_REALTIME, &start);
    prev = start;

    while (1) {
        u64 intervals, freq = 1000 MSEC, elapsed;
        struct timespec curr;

        clock_gettime(CLOCK_REALTIME, &curr);
        intervals = nsec_diff(prev, curr) + reminder;

        if (intervals < freq) {
	    usleep((freq - intervals) / (1 USEC));
            continue;
        }

        elapsed = nsec_diff(start, prev);
        for (i = 0; i < intervals/freq; i++) {
            print_marker(elapsed, !i ? eval_work(freq) : 0);
            elapsed += freq;
        }

        reminder = (intervals % freq);
        prev = curr;
    }
}

