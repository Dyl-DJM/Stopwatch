#include "ChronoSimple.h"

/* Auteur : Dylan DE JESUS
 * Creation : 1-03-2021
 * Modification : 7-03-2021 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <assert.h>

/*Ce programme constitue la deuxième partie de l'exercice 1
permettant d'afficher dans le format adéquat le chronomètre sur la sortie standard
*/

int formatAffichage(int duree){
    /*On s'assure que la durée donnée est bien positive*/
    assert(duree >= 0);
    printf("%d : %d : %d : %d\n", nb_ms_vers_heures(duree), nb_ms_vers_minutes(duree), nb_ms_vers_secondes(duree), nb_ms_vers_centiemes(duree));
    return 1;
}

#if 0
int main(void){
    int duree;

    /*On prend une première fois la valeur du temps à l'instant t pour la stocker dans temps_debut*/
    gettimeofday(&temps_debut, NULL);

    while(1){
        /*On prend une seconde fois la valeur du temps à l'instant t pour la stocker dans temps_fin*/
        gettimeofday(&temps_fin, NULL);
        duree = intervalle_ms(temps_debut, temps_fin);

        /*On effectue l'affichage dans le format donne*/
        formatAffichage(duree);

        /*On suspend le programme pendant 500 ms*/
        usleep(500000);
    }

    return 0;
}
#endif
