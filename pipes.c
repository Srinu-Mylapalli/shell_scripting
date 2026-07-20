//to illustrate pipes IPC#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

#define bs 256

int main()
{
    int pipe_fd[2];
    pid_t i_pid, j_pid;

    if (pipe(pipe_fd) == -1)
    {
        perror("pipe creation failed");
        return 1;
    }

    i_pid = vfork();

    if (i_pid == -1)
    {
        perror("process i creation failed");
        return 1;
    }

    if (i_pid == 0)
    {
        // Process I (Writer)
        close(pipe_fd[0]);

        char data[] = "Hello from process i";
        write(pipe_fd[1], data, strlen(data) + 1);

        close(pipe_fd[1]);
        _exit(0);
    }
    else
    {
        j_pid = vfork();

        if (j_pid == -1)
        {
            perror("process j creation failed");
            return 1;
        }

        if (j_pid == 0)
        {
            // Process J (Reader)
            close(pipe_fd[1]);

            char bfr[bs];
            read(pipe_fd[0], bfr, sizeof(bfr));

            printf("Process J received data: %s\n", bfr);

            close(pipe_fd[0]);
            _exit(0);
        }
        else
        {
            // Parent Process
            close(pipe_fd[0]);
            close(pipe_fd[1]);

            waitpid(i_pid, NULL, 0);
            waitpid(j_pid, NULL, 0);
        }
    }

    return 0;
}
