#include "PremPart.h"

/* Auteur : Dylan DE JESUS
 * Creation : 1-03-2021
 * Modification : 7-03-2021 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <assert.h>

/*Ce programme constitue la première partie de l'exercice 1
On y trouve les fonctions de conversions de milisecondes à d'autres unités
en plus d'une fonction calculant la durée entre deux temps en milisecondes
*/


struct timeval temps_debut, temps_fin;

int intervalle_ms(struct timeval debut, struct timeval fin){
    int msec, sec, usec;
    /*On prend le temps en secondes et micro secondes que l'on convertis en milisecondes
    pour les ajouter et renvoyer la valeur en ms
    */
    assert(debut.tv_sec >= 0);
    assert(fin.tv_sec >= 0);
    assert(debut.tv_usec >= 0);
    assert(fin.tv_usec >= 0);

    sec = (fin.tv_sec - debut.tv_sec);
    usec = (fin.tv_usec - debut.tv_usec);
    msec = (usec / 1000) + (sec * 1000);
    return msec;
}


int nb_ms_vers_centiemes(int nb_ms){
    return (nb_ms / 10) % 100;
}

int nb_ms_vers_secondes(int nb_ms){
    return (nb_ms / 1000 ) % 60;
}

int nb_ms_vers_minutes(int nb_ms){
    return (nb_ms / (1000 * 60)) % 60;
}

int nb_ms_vers_heures(int nb_ms){
    return (nb_ms / (1000 * 3600)) % 100;
}


/*Cette partie du programme est une partie de test du programme
afin de pouvoir tester les fonctions.
*/

#if 0
int main(void){
    int duree;

    /*On prend la valeur du temps donné à l'instant t dans temp_debut*/
    gettimeofday(&temps_debut, NULL);
    usleep(500000); /*On suspend le programme pendant 500 ms*/
    /*On prend la valeur du temps donné à l'instant t dans temp_fin*/
    gettimeofday(&temps_fin, NULL);

    /*On stocke la durée dans une variable*/
    duree = intervalle_ms(temps_debut, temps_fin);

    /*On teste les fonctions pour différentes valeurs*/
    printf("%d\n", nb_ms_vers_centiemes(1213));
    printf("%d\n", nb_ms_vers_minutes(3666666));
    printf("%d\n", nb_ms_vers_heures(3555555));

    return 0;
}
#endif

