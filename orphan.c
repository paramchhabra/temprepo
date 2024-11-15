#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();  // Create a child process

    if (pid == -1) {
        // Fork failed
        perror("fork failed");
        return 1;
    }
    if (pid == 0) {
        // Child process
        printf("Child Process: PID = %d, Parent PID = %d\n", getpid(), getppid());
        
        // Sleep for a few seconds to allow the parent to terminate
        // sleep(0.2);

        // Check the parent PID again after the parent has terminated
        printf("Child Process after Parent termination: PID = %d, Parent PID(init process) = %d\n", getpid(), getppid());
    } else {
        // Parent process
        // printf("%d is init process pid\n", getppid());
        printf("Parent Process: PID = %d, Child PID = %d\n", getpid(), pid);

        // Parent terminates immediately, making the child an orphan
        wait(NULL);
        _exit(0);
    }

    return 0;
}
