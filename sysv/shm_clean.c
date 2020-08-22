#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>

#include "shm_common.h"

int main(void) {

    int shm_id = -1;
    key_t shm_key = ftok(SHMKEY_FILE, 0);

    if (shm_key == -1) {
        perror("ftok failed");
        exit(1);
    }

    shm_id = shmget(shm_key, 0, SHMEM_FLAGS);
    if (shm_id == SHM_ERROR) {
        perror("shmget failed");
        exit(1);
    }

    // remove the shm segments
    if (shmctl(shm_id, IPC_RMID, NULL) == SHM_ERROR) {
        perror("shmctl failed");
        exit(1);
    } else {
        printf("Removed shmem: id=%u\n", shm_id);
    }
}