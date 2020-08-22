# Playing with Shared Memory

A sample code showing the usage of shared memory using

1. [POSIX interfaces](posix)
2. [System V interfaces](sysv)

Both the implementations were compiled and tested on macOS and Linux (Ubuntu 20.4) systems. Run `make` inside the subfolders to build for the target system. POSIX calls on Linux requires `-lrt` to run, so [Makefile](posix/Makefile) includes `-lrt` when building on Linux.
