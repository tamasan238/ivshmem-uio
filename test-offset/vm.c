#define SHM_NAME "/dev/uio0"
#define SHM_SIZE (PAGE_SIZE * 512)
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
    unsigned long offset = 0;

    for(int j = 0; j<512*1024; j++){
        for (int i = 0; i < 5; i++) {
            printf("%lu ", ptr[offset+i * (PAGE_SIZE / sizeof(unsigned long))]);
            if(ptr[offset+i * (PAGE_SIZE / sizeof(unsigned long))]==2){
                printf("%d\n", i+1);
                break;
            }
        }
        puts("");
        offset++;
    }

    munmap(shm_ptr, SHM_SIZE);
    close(fd);
    return 0;
}
