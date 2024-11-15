#include <stdio.h>
#include <unistd.h>
// #include <sys\wait.h>
// #include <sys\types.h>
#include <stdlib.h>

int main(){
    pid_t pid;

    pid = fork();

    if (pid<0)
    {
        printf("Fork Failed\n");
    }
    else if (pid==0)
    {
        printf("Child Process %d\n",getpid());
        sleep(5);
        printf("Child Process done executing\n");
    }
    else{
        printf("Parent process\n");
        sleep(10);
        exit(0);
    }

    return 0;
    
}