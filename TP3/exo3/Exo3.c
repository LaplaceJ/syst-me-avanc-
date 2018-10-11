#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void hand(int sig)
{
    if(sig == SIGINT)
    {
        printf("Interruption de %d par SIGINT\n",getpid());
        
    }
    else if(sig == SIGQUIT)
    {
        printf("Interruption de %d par SIGQUIT\n",getpid());
        
    }
    else
    {
        printf("Interruption de %d par %d\n",getpid(),sig);
    }
    exit(sig);
}

main()
{
    int fils;
    sigset_t ens;
    struct sigaction action;
    /* initialisation de la structure action */
    action.sa_handler = hand;
    sigemptyset(&ens);
    action.sa_mask = ens;
    action.sa_flags = 0;
    
    sigaction(SIGINT, &action,NULL);
    sigaction(SIGQUIT, &action,NULL);
    
    if( (fils=fork()) == -1)
    {
        perror("echec de fork");
        exit(1);
    }
    
    //fils
    if(fils == 0)
    {
       kill(getpid(),SIGINT); 
       for(;;);
       
    }
    //Pere 
    else 
    { 
        kill(getpid(),SIGQUIT);
        for(;;);
         
        
    }
    
    
    
}
