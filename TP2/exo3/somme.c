#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int arc, char* arg[])
{
    int n1,n2;
    n1=atoi(arg[1]);
    n2=atoi(arg[2]);
    printf("PID : %d; PPID : %d,%d + %d = %d\n", getpid(),getppid(),n1,n2,n1+n2);
    return 0;
    
}
