#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
    int tube[2];
    int fils1;
    int fils2;
    pid_t m;
    
    if(pipe(tube)<0)
    {
        perror("erreur ouverture pipe");
        exit(1);
    }
   

//  Création Fils 1
    if( ( fils1 = fork() ) < 0)
    {
        perror("Erreur fork");
        exit(1);
    }
//  Fils 1
    if(fils1 == 0)
    {
        close(tube[0]);
        close(1);
        dup(tube[1]);
        if(execlp("cat","cat","/etc/passwd", NULL)==-1)
        {
            perror("Echec cat");
            exit(1);
        }
    }
//  Fils 2 & Pere 
    else 
    {
//      Création Fils 2
        if( ( fils2 = fork() ) < 0)
        {
            perror("Erreur fork");
            exit(1);
        }
        
//      Fils 2
        if(fils2 == 0)
        {
            close(tube[1]);
            close(0);
            dup(tube[0]);
            if(execlp("wc","wc",NULL)==-1)
            {
                perror("Echec wc");
                exit(1);
            }
        }
        
//      Pere
        else
        {   close(tube[0]);
            close(tube[1]);
            if( ( m = wait(&fils1) ) < 0)
            {
                perror("Echec wait fils1");
                exit(1);
            }
            if( ( m = wait(&fils2) ) < 0)
            {
                perror("Echec wait fils2");
                exit(1);
            }
            printf("Fin du programme\n");
        }
    }
    
    return 0;
}
