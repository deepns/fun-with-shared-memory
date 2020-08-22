#include <stdio.h>
#include <stdlib.h> // for exit
#include <string.h> // for strncpy
#include <sys/shm.h> // for shm_ calls

#include "shm_common.h"

int main(int argc, char **argv) {
    int shm_id = -1;
    void *shm_addr = NULL;

    if (argc != 2) {
        printf("Usage: ./shm_write <message>\n");
        exit(1);
    }

    char *msg = argv[1];
    
    /*
     * Get a key from a dummy file.
     * The alternative way is to use our own key, but using
     * a file makes it easier to share with other programs.
     */
    key_t shm_key = ftok(SHMKEY_FILE, 0);
    if (shm_key == -1) {
        perror("ftok failed");
        exit(1);
    }

    /*
     * Creating the shared memory only from here.
     * Reader and Cleaner would fail if shared memory with the
     * key pointed by SHMKEY_FILE doesn't exist.
     */
    shm_id = shmget(shm_key, SHMEM_SIZE, IPC_CREAT | SHMEM_FLAGS);
    if (shm_id == SHM_ERROR) {
        perror("shmget failed");
        exit(1);
    }

    printf("shm_key=%u shm_id=%u\n", shm_key, shm_id);

    // if no flag is specified to shmat call, it will preserve
    // the permissions from the shmem.
    // shmat returns -1 on failure.
    shm_addr = shmat(shm_id, NULL, 0);
    if (shm_addr == (char *)SHM_ERROR) {
        perror("Failed to attach the memory");
        // Dont forget to remove the shm_id in case of failure.
        shmctl(shm_id, IPC_RMID, NULL);
        exit(1);
    }

    printf("Writing to shmem: shm_addr=%p msg=%s\n", shm_addr, msg);

    // write the given message to the shared memory
    strncpy((char *)shm_addr, msg, strlen(msg));

    // detach the mapped memory
    shmdt(shm_addr);

    // not removing the shmem from here.
    // it will be cleaned up separately from another program
    return 0;
}
