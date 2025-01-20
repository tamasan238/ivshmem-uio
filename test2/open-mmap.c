#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#define MMAP_SIZE 4096

void try_mmap(int fd, off_t offset, const char *path) {
    void *mapped = mmap(NULL, MMAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, offset);
    if (mapped == MAP_FAILED) {
        printf("mmap failed for %s at offset %ld: ", path, offset);
        perror("");
    } else {
        printf("Successfully mmap-ed %s at offset %ld.\n", path, offset);
        munmap(mapped, MMAP_SIZE);
    }
}

void try_open(const char *path) {
    int fd = open(path, O_RDWR);
    if (fd == -1) {
        perror(path);
        return;
    }

    printf("Successfully opened %s in READ/WRITE mode.\n", path);

    try_mmap(fd, 0, path);
    try_mmap(fd, 4096, path);

    close(fd);
}

int main() {
    try_open("/dev/uio0");
    try_open("/dev/shm/ivshmem");
    return 0;
}
