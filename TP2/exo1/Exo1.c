#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/*
Exécution du code

total 16
-rwxr-xr-x 1 msauvage gis4 8848 sept. 28 10:30 Exo1
-rw-r--r-- 1 msauvage gis4  314 sept. 28 10:30 Exo1.c

Q1/
execlp permet d'utiliser le chemin du path correspondant à la commande ls, le script de cette commande écrase le code (ainsi le printf contenu dans le else ne sera jamais executé) et c'est le code de la commande ls qui est executé.

Q2/
On supprime alors le code après le if sauf le return 0 sinon le compilateur refusera la compilation.
*/

int main()
{
    printf("Lancement de la commande ls");
    if(execlp("ls","ls","-l",NULL)==-1)
    {
        perror("echec execlp");
        exit(1);
    }
//     else
//     {
//         printf("fin de la commande ls\n");
//         exit(0);
//     }
     return 0;
}
