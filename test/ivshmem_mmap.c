#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <stdatomic.h>

typedef struct {
	atomic_flag p4processing;
}SharedData;

int main(void)
{
    int fd = open("/dev/shm/ivshmem", O_RDWR);
    if (fd < 0) {
        perror("open failed");
        return 1;
    }

    if (ftruncate(fd, sizeof(SharedData)) == -1) {
        perror("ftruncate failed");
        return 1;
    }

    SharedData* sharedData = mmap(NULL, sizeof(SharedData), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (sharedData == MAP_FAILED) {
        perror("mmap failed");
        return 1;
    }

    

    return 0;
}