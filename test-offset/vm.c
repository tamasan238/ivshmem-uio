#define SHM_NAME "/dev/uio0"
#define SHM_SIZE 524288

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

    int *ptr0 = (int *)shm_ptr;
    int *ptr1 = (int *)((char *)shm_ptr + 4096);
    int *ptr2 = (int *)((char *)shm_ptr + 4096 * 2);

    printf("先頭の数値: %d\n", *ptr0);
    printf("1ページ先の数値: %d\n", *ptr1);
    printf("2ページ先の数値: %d\n", *ptr2);

    munmap(shm_ptr, SHM_SIZE);
    close(fd);
    return 0;
}
