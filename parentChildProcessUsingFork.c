//to create parent and child process and, one adds all even numbers while other adds all odd numbers 

#include <stdio.h>
#include <unistd.h>

int main()
{
    int pid, i, se = 0, so = 0;

    pid = fork();

    if (pid != 0)
    {
        // Parent process
        for (i = 0; i < 20; i++)
        {
            if (i % 2 == 0)
            {
                se = se + i;   // Corrected
            }
        }

        printf("Sum of even numbers is %d\n", se);
    }
    else
    {
        // Child process
        for (i = 0; i < 20; i++)
        {
            if (i % 2 != 0)
            {
                so = so + i;
            }
        }

        printf("Sum of odd numbers is %d\n", so);
    }

    return 0;
}
