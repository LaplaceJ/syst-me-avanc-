#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
    int filsLs;
    pid_t m;
   

    
    if( ( filsLs = fork() ) < 0)
    {
        perror("Erreur fork");
        exit(1);
    }

//  Fils
    if(filsLs == 0)
    {
        int nf;
        if ( ( nf = open("dir.txt",2) ) < 0)
        {
            nf = creat("dir.txt",S_IRWXU | S_IRWXG);
        }
        else
        {
            lseek(nf,0,SEEK_END);
        }
        close(1);
        dup(nf) ;
        if(execlp("ls","ls", "-la", NULL)==-1)
        {
            perror("Echec ls ");
            exit(1);
        }
    }
//  Pere
    else 
    {
          if( ( m = wait(&filsLs) ) < 0)
            {
                perror("Echec wait ls");
                exit(1);
            }
    }
    
    return 0;
}
