#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// void hand(int sig)
// {
//     printf("Interruption de %d par %d\n",getpid(),sig);
//     exit(sig);
// }

main()
{
    int n;
    sigset_t ens;
    struct sigaction action;
    /* initialisation de la structure action */
    action.sa_handler = SIG_IGN;
    sigemptyset(&ens);
    action.sa_mask = ens;
    action.sa_flags = 0;
    
    sigaction(SIGINT, &action,NULL);
    
    if( (n=fork()) == -1)
    {
        perror("echec de fork");
        exit(1);
    }
    
    for(;;);
}
