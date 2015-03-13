/*
 * Best viewed with tabstop=3.
 *
 * Just an example of using the rdtsc with an asm
 * routine.
 *
 * LICENSE
 * 
 * I really don't care about what you'd like to do with this code, 
 * it wasn't that hard to make, but hey, i wont mind if you
 * liked it and want to buy me a beer ;)
 *
 * AUTHOR:
 *	marcelog@gmail.com
 *
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <mraa.h>
#include "node/uv.h"

extern void rdtsc(long long *p);

static uv_thread_t thread;

static void thread_cb(void* arg) {
}

int
main(void)
{
    unsigned long long x, y;
    x = 0; y = 0;
    fprintf(stdout, "%llu & %llu\n", x, y);

    mraa_i2c_context bus;
    uint8_t buf[2];
    int ret;

    bus = mraa_i2c_init(0);
    mraa_i2c_address(bus, 0x77);
    if (mraa_i2c_read_byte_data(bus, 0xd0) != 0x55) {
        fprintf(stderr, "There is an issue with your sensor buddy!");
    }
    mraa_i2c_write_byte_data(bus, 0xf4, 0x2e);

    rdtsc(&x);

// do something
//    mraa_i2c_write(bus, buf, 3);
//    ret = mraa_i2c_read(bus, buf, 2);
    sleep(1);
// do something

    rdtsc(&y);

    if (ret != 2) {
        fprintf(stderr, "crap\n");
    }
    fprintf(stdout, "%llu & %llu\n", x, y);

    fprintf(stdout, "%llu\n", y-x);


    rdtsc(&x);
    uv_thread_create(&thread, thread_cb, NULL);
    /* pause execution of this thread until the spawned thread has had
     * time to finish execution. */
    uv_thread_join(&thread);
    rdtsc(&y);

    fprintf(stdout, "%llu & %llu\n", x, y);

    fprintf(stdout, "%llu\n", y-x);

    return EXIT_SUCCESS;
}

