#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>


int main()
{
    int pid;
    pid_t m;
    char chemin[20];
    printf("Saisir le path du fichier : \n");
    scanf("%s",chemin);
    printf("%s\n",chemin);
    
    
    if( ( pid = fork() ) < 0)
    {
        perror("Erreur fork");
        exit(1);
    }
    if(pid > 0)
    {
        if( ( m = wait(&pid) ) < 0)
        {
            perror("Erreur wait");
            exit(1);
        }
    }
    else
    {
        if(execlp("wc","wc","-l",chemin,NULL)==-1)
        {
            perror("echec execlp");
            exit(1);
        }
    }
    
    return 0;
}
