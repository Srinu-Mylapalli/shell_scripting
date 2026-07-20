//Program to Demonstrate Process Creation Using fork() and Process Termination Using wait()
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    int pid, cpid, status;

    pid = fork();

    if (pid < 0)
    {
        printf("Fork failed\n");
        exit(1);
    }

    if (pid != 0)
    {
        // Parent process
        printf("I am the parent with PID %d\n", getpid());

        cpid = wait(&status);

        printf("Child process %d terminated with status %d\n",
               cpid, WEXITSTATUS(status));
    }
    else
    {
        // Child process
        printf("I am the child with PID %d\n", getpid());

        exit(2);
    }

    return 0;
}
