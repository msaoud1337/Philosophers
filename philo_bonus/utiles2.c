#include <stdio.h>
#include <unistd.h>

int main()
{
    int pid;

    pid = fork();
    if (pid == -1)
    {
        printf("fork failed");
        return (0);
    }
    if (pid > 0)
        printf("we are in the parent procces %d\n",pid);
    if (pid == 0)
        printf("we are in the child procces %d\n", pid);
}