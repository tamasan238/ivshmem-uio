#define SHM_NAME "/dev/uio0"
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

    void *shm_ptr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 4096);
    if (shm_ptr == MAP_FAILED) {
        perror("mmap");
        close(fd);
        exit(EXIT_FAILURE);
    }

    unsigned long *ptr = (unsigned long *)shm_ptr;
    printf("1ページ目: %lu\n", ptr[0]);
    printf("2ページ目: %lu\n", ptr[PAGE_SIZE / sizeof(unsigned long)]);
    printf("3ページ目: %lu\n", ptr[2 * (PAGE_SIZE / sizeof(unsigned long))]);

    munmap(shm_ptr, SHM_SIZE);
    close(fd);
    return 0;
}
