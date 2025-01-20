#define SHM_NAME "/dev/uio0"
#define SHM_SIZE 524288 // 512 * 1024

#include <stdio.h>
#include <fcntl.h>     // open()
#include <sys/mman.h>  // mmap(), munmap()
#include <unistd.h>    // close()
#include <stdlib.h>    // exit()
#include <string.h>    // memcpy()

int main(){
	int fd = open(SHM_NAME, O_RDWR);

    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    printf("fd: %d，SHM_SIZE: %d\n", fd, SHM_SIZE);
    
    int offset;
    printf("offset を選択してください (0 または 4096): ");
    if (scanf("%d", &offset) != 1 || (offset != 0 && offset != 4096)) {
        fprintf(stderr, "invalid value\n");
        close(fd);
        exit(EXIT_FAILURE);
    }

    void *shm_ptr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, offset);
    if (shm_ptr == MAP_FAILED) {
        perror("mmap");
    	close(fd);
        exit(EXIT_FAILURE);
    }

    printf("SHM opened.\n");
    printf("mapped to %p\n", shm_ptr);
    
    int choice;
    printf("処理を選択してください (1: 読み取り, 2: 書き込み): ");
    if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2)) {
        fprintf(stderr, "invalid input\n");
        munmap(shm_ptr, SHM_SIZE);
        close(fd);
        exit(EXIT_FAILURE);
    }

    if (choice == 1) {
        printf("メモリの最初のデータ: %s\n", (char *)shm_ptr);
    } else if (choice == 2) {
        memcpy(shm_ptr, "p4", strlen("p4") + 1);
        printf("メモリの最初のデータ: %s\n", (char *)shm_ptr);
    }
    
    munmap(shm_ptr, SHM_SIZE);
    close(fd);
    return 0;
}