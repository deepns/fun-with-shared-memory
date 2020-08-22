#include <fcntl.h> // for flags O_CREAT etc..
#include <stdio.h>
#include <stdlib.h> // for EXIT_SUCCESS, EXIT_FAILURE
#include <string.h>
#include <sys/mman.h> // for mmap, shm_open
#include <unistd.h> // for close()

#include "shm_common.h"

int main(int argc, char **argv) {

    int fd = -1;

    if (argc != 2) {
        printf("Usage: ./shm_write <message>\n");
        return EXIT_FAILURE;
    }

    fd = shm_open(SHM_NAME, SHM_FLAGS, SHM_MODE);
    if (fd == -1) {
        perror("shm_open failed");
        return EXIT_FAILURE;
    }

    // extend the shmem size
    ftruncate(fd, SHM_SIZE);

    // map some memory to shmem segment to write to.
    void *shm_addr = NULL;
    shm_addr = mmap(NULL, SHM_SIZE, PROT_WRITE, MAP_SHARED, fd, 0);
    if (shm_addr == MAP_FAILED) {
        perror("mmap failed");
        return EXIT_FAILURE;
    }

    char *msg = argv[1];
    printf("Writing to shmem: name=%s, msg=%s, shm_addr=%p\n",
            SHM_NAME, msg, shm_addr);
    strncpy((char *)shm_addr, msg, strlen(msg));

    // unmap the memory and close the file descriptor
    munmap(shm_addr, SHM_SIZE);
    close(fd);

    return EXIT_SUCCESS;
}
