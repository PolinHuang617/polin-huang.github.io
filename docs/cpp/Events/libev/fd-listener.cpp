#include <cstdio>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fd = open("t.cpp", O_RDONLY);
    if (fd == -1)
        return -1;

    printf("t.cpp fd: %d\n", fd);
    close(fd);

    return 0;
}
