#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h> // for sleep

#include "shm_common.h"

int main(void) {

    int shm_id = -1;
    char *shm_addr;
    key_t shm_key = -1;
    
    shm_key = ftok(SHMKEY_FILE, 0);

    if (shm_key == -1) {
        perror("ftok failed");
        exit(1);
    }

    /*
     * If a segment with shm_key exists already, then shmget
     * returns the id of the existing segment. Size option is
     * ignored in that case.
     * If a segment with shm_key doesn't exist, and if IPC_CREAT
     * flag is passed, then a new segment will be created with
     * with the given size.
     */
    shm_id = shmget(shm_key, SHMEM_SIZE, SHMEM_FLAGS);
    if (shm_id == SHM_ERROR) {
        perror("shmget failed");
        exit(1);
    }

    printf("shm_key=%u shm_id=%d\n", shm_key, shm_id);

    /*
     * if we don't specify the address to attach the shared memory,
     * address returned from shmat after each invocation will be different
     * though the shm_id could be same
     */
    shm_addr = shmat(shm_id, NULL, 0);
    if (shm_addr == (char *)SHM_ERROR) {
        perror("shmat failed");
        exit(1);
    }

    // reading from shared memory
    printf("Reading from shmem: shm_addr=%p msg=%s\n", shm_addr, shm_addr);

    return 0;
}
