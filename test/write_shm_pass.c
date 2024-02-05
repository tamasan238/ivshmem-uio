#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int main(void)
{
    int fd;
    char *map_region;

    fd = open("/dev/uio0", O_RDWR);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    map_region = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd,
                      4096);
    if (map_region < 0) {
        perror("mmap");
        exit(1);
    }

    printf("mapped to %p\n", map_region);

    strcpy(map_region, "pass");
    printf("wrote\n");
    
    munmap(map_region, 4096);
    close(fd);

    return 0;
}
