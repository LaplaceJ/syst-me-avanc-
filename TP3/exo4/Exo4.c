#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handFils(int sig)
{
    printf("Le fils est mort",getpid(),sig);
    exit(sig);
}

void handPere(int sig)
{
    printf("Le pere est mort",getpid(),sig);
    exit(sig);
}


main()
{
    int fils;
    
    
    
    if( (fils=fork()) == -1)
    {
        perror("echec de fork");
        exit(1);
    }
    
    //fils
    if(fils == 0)
    {
        sigset_t ens;
        struct sigaction action;
        /* initialisation de la structure action */
        action.sa_handler = handFils;
        sigemptyset(&ens);
        action.sa_mask = ens;
        action.sa_flags = 0;
        
        sigaction(SIGINT, &action,NULL);
    
       kill(getpid(),SIGINT); 
       for(;;);
       
    }
    //Pere 
    else 
    { 
        sigset_t ens;
        struct sigaction action;
        /* initialisation de la structure action */
        action.sa_handler = handPere;
        sigemptyset(&ens);
        action.sa_mask = ens;
        action.sa_flags = 0;
        
        sigaction(SIGINT, &action,NULL);
        kill(getpid(),SIGINT);
        for(;;);
         
        
    }
    
    
    
}
