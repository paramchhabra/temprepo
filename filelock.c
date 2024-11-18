#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>

int main() {
    const char *filename = "example.txt";
    
    // Open the file for reading and writing
    int fd = open(filename, O_RDWR | O_CREAT, 0666);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Attempt to lock the file
    if (flock(fd, LOCK_EX | LOCK_NB) == -1) {  // LOCK_EX: Exclusive lock; LOCK_NB: Non-blocking
        perror("File is already locked by another process");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("File locked successfully.\n");

    // Simulate some processing on the file
    printf("Processing file...\n");
    sleep(10); // Replace with actual file operations

    // Unlock the file
    if (flock(fd, LOCK_UN) == -1) {
        perror("Error unlocking file");
    } else {
        printf("File unlocked successfully.\n");
    }

    // Close the file descriptor
    close(fd);

    return 0;
}
