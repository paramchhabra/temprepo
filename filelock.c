#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

// Function to acquire a read lock
int lock_file_read(int fd) {
    struct flock lock;
    lock.l_type = F_RDLCK;  // Read lock
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;       // Lock from the beginning of the file
    lock.l_len = 0;         // Lock the entire file

    if (fcntl(fd, F_SETLK, &lock) == -1) {
        if (errno == EACCES || errno == EAGAIN) {
            printf("Read lock failed: File is locked by another process\n");
        } else {
            perror("Read lock failed");
        }
        return -1;  // Locking failed
    }
    printf("Read lock acquired successfully\n");
    return 0;  // Locking successful
}

// Function to acquire a write lock
int lock_file_write(int fd) {
    struct flock lock;
    lock.l_type = F_WRLCK;  // Write lock
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;       // Lock from the beginning of the file
    lock.l_len = 0;         // Lock the entire file

    if (fcntl(fd, F_SETLK, &lock) == -1) {
        if (errno == EACCES || errno == EAGAIN) {
            printf("Write lock failed: File is locked by another process\n");
        } else {
            perror("Write lock failed");
        }
        return -1;  // Locking failed
    }
    printf("Write lock acquired successfully\n");
    return 0;  // Locking successful
}

// Function to unlock a file
int unlock_file(int fd) {
    struct flock lock;
    lock.l_type = F_UNLCK;  // Unlock
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;       // Unlock from the beginning of the file
    lock.l_len = 0;         // Unlock the entire file

    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("Error unlocking file");
        return -1;  // Unlocking failed
    }
    printf("File unlocked successfully\n");
    return 0;  // Unlocking successful
}

// Function to read data from a file with a read lock
void read_file(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return;
    }

    if (lock_file_read(fd) == 0) {
        char buffer[1024];
        ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1);
        if (bytesRead > 0) {
            buffer[bytesRead] = '\0';  // Null-terminate the string
            printf("Data read: %s\n", buffer);
        } else {
            printf("No data to read or error occurred\n");
        }
        unlock_file(fd);
    }

    close(fd);
}

// Function to write data to a file with a write lock
void write_file(const char *filename, const char *data) {
    int fd = open(filename, O_WRONLY | O_CREAT, 0666);
    if (fd == -1) {
        perror("Error opening file");
        return;
    }

    if (lock_file_write(fd) == 0) {
        if (write(fd, data, strlen(data)) == -1) {
            perror("Error writing to file");
        } else {
            printf("Data written successfully\n");
        }
        unlock_file(fd);
    }

    close(fd);
}

// Main function
int main() {
    const char *filename = "testfile.txt";

    // Writing to the file
    write_file(filename, "Hello, File Locking!\n");

    // Reading from the file
    read_file(filename);

    return 0;
}
