#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int arc, char* argv[])
{
    int filsWho,filsPs,filsLs;
    pid_t m;
    
    if( ( filsWho = fork() ) < 0)
    {
        perror("Erreur fork");
        exit(1);
    }

//  Pere
    if(filsWho > 0)
    {
        if( ( m = wait(&filsWho) ) < 0)
            {
                perror("Echec wait ps");
                exit(1);
            }
            
        if( ( filsPs = fork() ) < 0)
        {
            perror("Erreur fork ps");
            exit(1);
        }
        
        //Pere
        if (filsPs > 0)
        {
            
            if( ( m = wait(&filsPs) ) < 0)
            {
                perror("Echec wait ps ");
                exit(1);
            }
                
            if( ( filsLs = fork() ) < 0)
            {
                perror("Erreur fork ls ");
                exit(1);
            }
            
            //Pere
            if (filsLs > 0)
            {
                if( ( m = wait(&filsLs) ) < 0)
                {
                    perror("Echec wait");
                    exit(1);
                }
            }
            //fils ls
            else{
                if(execlp("ls","ls", "-la", NULL)==-1)
                {
                    perror("Echec ls ");
                    exit(1);
                }
            }
            
            
        }
//      fils 2
        else if(filsPs == 0)
        {
            if(execlp("ps","ps" , "-x",NULL)==-1)
            {
                perror("Echec ps");
                exit(1);
            }
        }
        
    }
//  fils 1
    else if(filsWho == 0)
    {
        if(execlp("who","who",NULL)==-1)
        {
            perror("Echec who");
            exit(1);
        }
    }
    
    return 0;
}
