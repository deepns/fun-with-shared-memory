#ifndef __SHM_COMMON_H__
#define __SHM_COMMON_H__

/*
 * Common definitions for the reader and writers
 * of the shared memory
 */

#define SHM_NAME "/shm_posix"
#define PAGE_SIZE 4096
#define NUM_PAGES 2048
#define SHM_SIZE (NUM_PAGES * PAGE_SIZE)
#define SHM_FLAGS (O_CREAT | O_RDWR)
#define SHM_MODE (S_IRUSR | S_IWUSR)

#endif // __SHM_COMMON_H__
