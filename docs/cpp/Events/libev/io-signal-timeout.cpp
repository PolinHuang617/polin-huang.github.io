#include <cstdio>
#include <csignal>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>

#include "deps/libev/ev.h"

ev_io io_w;
ev_timer timer_w;
ev_signal signal_w;
ev_stat stat_w;

void io_action(struct ev_loop *main_loop, ev_io *io_w, int event) {
    int rst;
    char buf[1024] = {'\0'};
    puts("in io callback\n");
    read(STDIN_FILENO, buf, sizeof(buf));
    printf("Read in a string %s\n", buf);
    ev_io_stop(main_loop, io_w);
}

void timer_action(struct ev_loop *main_loop, ev_timer *timer_w, int event) {
    puts("in timer callback\n");
    ev_timer_stop(main_loop, timer_w);
}

void signal_action(struct ev_loop *main_loop, ev_signal *signal_w, int event) {
    puts("in signal callback\n");
    ev_signal_stop(main_loop, signal_w);
    ev_break(main_loop, EVBREAK_ALL);
}

void stat_action(struct ev_loop *main_loop, ev_stat *stat_w, int event) {
    printf("watch %s\n", stat_w->path);
    ev_stat_stop(main_loop, stat_w);
}

int main(int argc, char *argv[]) {
    struct ev_loop *main_loop = ev_default_loop(0);

    ev_init(&io_w, io_action);
    ev_io_set(&io_w, STDIN_FILENO, EV_READ);

    ev_init(&timer_w, timer_action);
    ev_timer_set(&timer_w, 2, 0);

    ev_init(&signal_w, signal_action);
    ev_signal_set(&signal_w, SIGINT);

    ev_init(&stat_w, stat_action);
    ev_stat_set(&stat_w, "/root/t.txt", EV_READ);

    ev_io_start(main_loop, &io_w);
    ev_timer_start(main_loop, &timer_w);
    ev_signal_start(main_loop, &signal_w);
    ev_stat_start(main_loop, &stat_w);

    ev_run(main_loop, 0);

    ev_loop_destroy(main_loop);

    return 0;
}
