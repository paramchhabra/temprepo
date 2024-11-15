#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void addnum(int a, int b){
    printf("Sum is : %d\n",a+b);
}

int main(){
    pid_t pid;

    pid = fork();

    if(pid<0){
        printf("Forking error");
    }
    else if (pid==0)
    {
        printf("This is a child process %d\n",getpid());
        printf("Parent id %d\n", getppid());
        sleep(5);
        addnum(5,3);
    }
    else{
        printf("This is parent process %d\n", getpid());
        printf("child pid %d\n",pid);
        wait(NULL);
    }
    
    return 0;

}