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
        int nb;
        printf("Saisir une suite d'entier terminée par 0\n");
        scanf("%d",&nb);
        while(nb != 0)
        {
            if(nb%2 == 0)
            {
                write(tube[1],&nb,sizeof(int));
            }
            scanf("%d",&nb);
        }
        close(tube[1]);
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
            int nb;
            int S;
            S = atoi(argv[1]);
            while(read(tube[0],&nb,sizeof(int))==sizeof(int))
            {
                if(nb>S)
                {
                    printf("%d est supérieur à %d\n",nb,S);
                }
            }
            close(tube[0]);
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
