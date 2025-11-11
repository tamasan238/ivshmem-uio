#define SHM_NAME "/dev/uio0"
#define SHM_SIZE 1048576
#define PAGE_SIZE 4096

#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int fd = open(SHM_NAME, O_RDWR);
    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    void *shm_ptr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 4096);
    if (shm_ptr == MAP_FAILED) {
        perror("mmap");
        close(fd);
        exit(EXIT_FAILURE);
    }

    unsigned long *ptr = (unsigned long *)shm_ptr;

    for (int i = 0; i < 512; i++) {
        printf("ページ %d: %lu\n", i + 1, ptr[i * (PAGE_SIZE / sizeof(unsigned long))]);
    }

    munmap(shm_ptr, SHM_SIZE);
    close(fd);
    return 0;
}
