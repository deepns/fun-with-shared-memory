#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#include "shm_common.h"

int main(void) {

    void *shm_addr = NULL;
    int shm_fd = -1;

    shm_fd = shm_open(SHM_NAME, O_RDONLY, SHM_MODE);
    if (shm_fd == -1) {
        perror("shm_open failed");
        return EXIT_FAILURE;
    }

    shm_addr = mmap(NULL, SHM_SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (shm_addr == MAP_FAILED) {
        perror("mmap with shm_fd failed");
        return EXIT_FAILURE;
    }

    printf("Reading from addr=%p, msg=%s\n", shm_addr, (char *)shm_addr);

    // getting some stats about the shared memory just accessed.
    struct stat shmstat;
    fstat(shm_fd, &shmstat);

#ifdef __linux__
    printf("shm_stats: st_size=%ld, st_blocks=%ld, st_blksize=%ld\n",
            shmstat.st_size,
            shmstat.st_blocks,
            shmstat.st_blksize);
#elif defined(__MACH__) || defined(__APPLE__)
    /*
     * macOS doesn't provide the file system interface to access
     * shared memory segments. So the blocks and blksize fields
     * are not populated in the stat results.
     */
    printf("shm_stats: st_size=%lld\n", shmstat.st_size);
#endif

    printf("Cleaning up %s segment\n", SHM_NAME);
    // do the necessary cleanup.
    munmap(shm_addr, SHM_SIZE);
    close(shm_fd);
    shm_unlink(SHM_NAME);

    return EXIT_SUCCESS;
}
