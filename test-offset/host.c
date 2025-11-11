#define SHM_NAME "/dev/shm/ivshmem"
#define SHM_SIZE 524288
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

    void *shm_ptr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (shm_ptr == MAP_FAILED) {
        perror("mmap");
        close(fd);
        exit(EXIT_FAILURE);
    }

    unsigned long *ptr = (unsigned long *)shm_ptr;

    for (int page = 0; page < 3; page++) {
        for (int i = 0; i < 256; i++) {
            ptr[page * (PAGE_SIZE / sizeof(unsigned long)) + i] = i + 1;
        }
    }

    for (int page = 0; page < 3; page++) {
        printf("%dページ目: ", page + 1);
        for (int i = 0; i < 256; i++) {
            printf("%lu ", ptr[page * (PAGE_SIZE / sizeof(unsigned long)) + i]);
        }
        printf("\n");
    }

    munmap(shm_ptr, SHM_SIZE);
    close(fd);
    return 0;
}
