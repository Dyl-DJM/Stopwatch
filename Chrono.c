#include "Chrono.h"

/* Auteur : Dylan DE JESUS
 * Creation : 1-03-2021
 * Modification : 7-03-2021 */

#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <assert.h>


/*Ce programme traite l'ensemble des question de l'exercice 3, il permet
l'affichage final, de la version graphique et améliorée du chronomètre demandé
*/


int conversionMilisecondes(char lettre){
    int val;

    val = 0;

    /*On s'assure que la valeur ASCII de la lettre est superieures à 0*/
    assert(lettre >= 0);

    /*Selon la valeur de la lettre
    H -> Heures
    M -> Minutes
    S -> Secondes
    C -> Centièmes
    */

    switch(lettre){
        case 'H':{
            val = 3.6 * 1000000;
            break;
        }
        case 'M':{
            val = 60000;
            break;
        }
        case 'S':{
            val = 1000;
            break;
        }
        case 'C':{
            val = 1000 / 10;
            break;
        }
    }
    return val;
}

/*Programme principal de tout le projet*/

int main(void){
    int touche, etat_programme, minuteur;
    Chronometre chrono;

    /*Initialisation du chrono*/
    chrono = initialiser_chronometre();

    /*Definition de la fenêtre graphique et autres options*/
    initscr();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    cbreak();

    /*Definition de la couleur on definit 5 paires*/
    start_color();
    init_pair(1,COLOR_YELLOW, COLOR_BLACK);
    init_pair(2,COLOR_GREEN, COLOR_BLACK);
    init_pair(3,COLOR_RED, COLOR_BLACK);
    init_pair(4,COLOR_CYAN, COLOR_BLACK);
    init_pair(5,COLOR_WHITE, COLOR_BLACK);

    /*L'état du programme vaut activité*/
    etat_programme = 1;

    gettimeofday(&temps_debut, NULL);

    /*Tant que l'état du programme est en activité on continue*/
    while(etat_programme == 1){
        /*L'utilisateur appuie sur une touche*/
        touche = getch();

        /*Dimensions de la fenêtre obligatoire*/
        if((LINES < 14) || (COLS < 58)){
            printf("Taille de fenêtre insuffisante");
            exit(EXIT_FAILURE);
        }

        /*TOUCHES : F1, F2, F3......F6*/
        if(touche==KEY_F(1)){
            if(nb_ms_vers_heures(chrono.avertissement) < 99)
                chrono.avertissement += conversionMilisecondes('H');
        }
        if(touche==KEY_F(2)){
            if(nb_ms_vers_heures(chrono.avertissement) > 0)
                chrono.avertissement -= conversionMilisecondes('H');
        }

        if(touche==KEY_F(3)){
            if(nb_ms_vers_minutes(chrono.avertissement) < 60)
                chrono.avertissement += conversionMilisecondes('M');
        }
        if(touche==KEY_F(4)){
            if(nb_ms_vers_minutes(chrono.avertissement) > 0)
                chrono.avertissement -= conversionMilisecondes('M');
        }

        if(touche==KEY_F(5)){
            if(nb_ms_vers_secondes(chrono.avertissement) < 60)
                chrono.avertissement += conversionMilisecondes('S');
        }
        if(touche==KEY_F(6)){
            if(nb_ms_vers_secondes(chrono.avertissement) > 0)
                chrono.avertissement -= conversionMilisecondes('S');
        }

        /*TOUCHE : 't' on marque le tour*/
        if(touche == 't')
            ajouter_tour(&chrono);

        /*TOUCHE : 'r' on reinitialise le chronometre*/
        if(touche == 'r'){
            /*l'état, la duree, le nombre de tour et l'indice du dernier tour retourn à 0*/
            chrono.duree = 0;
            chrono.etat = 0;
            chrono.nb_tour = 0;
            chrono.indice_der_tour = 0;
        }

        /*TOUCHE : 'q' on quitte le programme*/
        if(touche == 'q'){
            /*On change la valeur de etat du programme*/
            etat_programme = 0;
        }

        /*TOUCHE : ESPACE on change l'état*/
        if(touche == ' '){
            if(chrono.etat == 0){
                gettimeofday(&temps_debut, NULL);
                chrono.etat = 1;
            }
            else{
                chrono.etat = 0;
            }
        }
        /*Petit temps de pause*/
        usleep(50000);

        if(chrono.etat == 1){
            gettimeofday(&temps_fin, NULL);
            chrono.duree += intervalle_ms(temps_debut, temps_fin);
            temps_debut = temps_fin;
        }
        clear();
        /*La durée est plus grande que celle de l'alarme et c'est la première fois donc on affiche
        visuellement*/
        if(chrono.duree >= chrono.avertissement && minuteur == 0){
            afficher_flash();
            /*ici on précise que l'on a déjà averti l'utilisateur*/
            minuteur = 1;
        }
        if(chrono.duree < chrono.avertissement)
            minuteur = 0;

        /*On affiche tout cela graphiquement*/
        afficher_interface(chrono);
        refresh();
    }
    endwin();
    return 0;
}
