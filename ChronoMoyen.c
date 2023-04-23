#include "ChronoMoyen.h"

/* Auteur : Dylan DE JESUS
 * Creation : 1-03-2021
 * Modification : 7-03-2021 */

#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <assert.h>

/*Ce programme constitue la troisème et dernière partie de l'exercice 1
permettant d'afficher graphiquement un protoype de chronomètre avec certaines options
comme la réinitialisation, .... d'après un algorithme.
*/

int formatAffichageGraphique(int x, int  y,int duree){
    /*On s'assure que les coordonnées rentrent bien dans la fenêtre*/
    assert(x >= 0);
    assert(x >= 0);

    /*Affichage formaté*/
    mvprintw(y, x, "%d : %d : %d : %d\n", nb_ms_vers_heures(duree), nb_ms_vers_minutes(duree), nb_ms_vers_secondes(duree), nb_ms_vers_centiemes(duree));
    return 1;
}

/*Partie du programme test*/

#if 0
int main(void){
    int duree_totale, etat, touche;

    /*Definition de l'ecran et autres otpions*/
    initscr();
    nodelay(stdscr, TRUE);
    cbreak();

    /*Initialisation de la variable de durée, et chronometre à l'état de pause*/
    duree_totale = 0;
    etat = 0;

    /*On récupère le premier temps*/
    gettimeofday(&temps_debut, NULL);

    while(1){
        touche = getch();

        /*Touche espace*/
        if(touche == ' '){
            /*L'état vaut 0 on le change et on met une valeur de temps dans temps_debut*/
            if(etat == 0){
                gettimeofday(&temps_debut, NULL);
                etat = 1;
            }
            else{
                /*On met l'état sur pause*/
                etat = 0;
            }
        }
        usleep(50000); /*500 ms*/

        if(etat == 1){
            /*Le chronometre est en état actif, on calcule la nouvelle durrée*/
            gettimeofday(&temps_fin, NULL);
            duree_totale += intervalle_ms(temps_debut, temps_fin);
            temps_debut = temps_fin;
        }

        /*On efface les anciennes valeurs pour afficher les nouvelles de manière formatée*/
        clear();
        formatAffichageGraphique(0, 0, duree_totale);
        refresh();

    }
    /*Fermeture de fenêtre*/
    endwin();
    return 0;
}
#endif
