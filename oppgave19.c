#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main()
{
    pid_t pid;
    // creating child process and storing the returned PID
    pid = fork();
    //if pid greater than 0 then the code inside if statement is being executed by parent process
    if(pid > 0)
    {
        printf("This is the parent process");
        sleep(10);
    }
    else if (pid == 0) 
    // this code is being executed by child process
    {
        
        printf("This is the child process");
        // terminating the child process
        exit(0);
    }
    return 0;
}
