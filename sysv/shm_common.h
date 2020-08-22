#ifndef __SHM_COMMON_H__
#define __SHM_COMMON_H__

/*
 * Common definitions for the reader and writers
 * of the shared memory
 */

#define PAGE_SIZE 4096 // 4K page size
#define SHMEM_SIZE (1024 * PAGE_SIZE) // 4MB
#define SHMEM_FLAGS (SHM_R | SHM_W)
#define SHMKEY_FILE "shmkey.txt"

// making error check easier since -1
// indicates error in return status of most ipc calls
#define SHM_ERROR (-1)

#endif // __SHM_COMMON_H_
