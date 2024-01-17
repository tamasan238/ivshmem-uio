#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

int main(void)
{
    int fd;
    char *addr;
    
    fd = open("/dev/shm/ivshmem", O_RDWR);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    addr = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    printf("shm: %s\n", addr);

    return 0;
}
