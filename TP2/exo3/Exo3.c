#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int arc, char* argv[])
{
    int fils1,fils2,n1;
    pid_t m;
    
    if( ( fils1 = fork() ) < 0)
    {
        perror("Erreur fork");
        exit(1);
    }

//  Pere
    if(fils1 > 0)
    {
        if( ( fils2 = fork() ) < 0)
        {
            perror("Erreur fork");
            exit(1);
        }
        
        if (fils2 > 0)
        {
            n1 = fils1 ; 
            
            if( ( m = wait(&fils1) ) < 0)
            {
                perror("Echec wait");
                exit(1);
            }
            
            if( n1 == m)
            {
                printf("Somme effectuée\n");
            }
            else
            {
                printf("Produit effectuée\n");
            }
            
            if( ( m = wait(&fils2) ) < 0)
            {
                perror("Echec wait");
                exit(1);
            }
            
            if( n1 == m)
            {
                printf("Somme effectuée\n");
            }
            else
            {
                printf("Produit effectuée\n");
            }
        }
//      fils 2
        else if(fils2 == 0)
        {
            if(execl("produit","./produit",argv[1],argv[2],NULL)==-1)
            {
                perror("Echec produit");
                exit(1);
            }
        }
        
    }
//  fils 1
    else if(fils1 == 0)
    {
        if(execl("somme","./somme",argv[1],argv[2],NULL)==-1)
        {
            perror("Echec somme");
            exit(1);
        }
    }
    
    return 0;
}
