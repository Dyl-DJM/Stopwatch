#include "Ex2.h"

/* Auteur : Dylan DE JESUS
 * Creation : 1-03-2021
 * Modification : 7-03-2021 */

#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>

/*Ce programme traite l'ensemble des question de l'exercice 2, il contient
toutes les fonctions à vocation graphiques.
*/




Chronometre initialiser_chronometre(){
    /*On definit un chronometre local à la fonction que l'on renverra*/
    Chronometre chrono;

    /*Initialisation des champs du chronomètres selon le cahier des charges*/
    chrono.etat = 0;
    chrono.duree = 0;
    chrono.avertissement = 25000;
    chrono.indice_der_tour = 0;
    chrono.nb_tour = 0;

    return chrono;
}


void afficher_options(){
    int i, x_milieu, y_milieu;

    /*Calcul des coordonnées du milieu de fenêtre*/
    x_milieu = COLS / 2;
    y_milieu = LINES / 2;

    /*Affichage de la ligne sur toute la largeur*/
    for(i = 0; i < COLS; i++){
        mvaddch(LINES -8 ,i,'-');
    }

    /*On affiche les options*/
    mvprintw(LINES -7,0,"Espace : lancer/ mettre en pause");
    mvprintw(LINES -6,0,"r : réinitialisé");
    mvprintw(LINES -5,0,"t : marquer tour");
    mvprintw(LINES -4,0,"F1/F2 : incrémenter/ décrémenter heure avertissement");
    mvprintw(LINES -3,0,"F3/F4 : incrémenter/ décrémenter minute avertissement");
    mvprintw(LINES -2,0,"F5/F6 : incrémenter/ décrémenter seconde avertissement");
    mvprintw(LINES - 1,0,"q : quitter");
}

void afficher_interface(Chronometre chrono){
    int i, x_milieu, y_milieu;

    /*Calcul des coordonnées du milieu de fenêtre*/
    x_milieu = COLS / 2;
    y_milieu = LINES / 2;

    /*Affichage des textes qui resteront inchangés pendant tout le programme*/
    mvprintw(0, x_milieu - 9, "== Chronometre ==");
    mvprintw(LINES - 9, x_milieu - 15 - 9, "Avertissement :");

    /*Affichage formatée de ma durée du chronometre et du minuteur d'alerte*/
    formatAffichageGraphique(x_milieu, LINES - 10, chrono.duree);
    formatAffichageGraphique(x_milieu, LINES - 9, chrono.avertissement);

    /*Pour chaque tour marqué par l'utilisateur on ecrit le tour*/
    for(i = 0; i < chrono.nb_tour; i++){
        /*Si le nombre de tour tient sans suppression d'ancien tour*/
        if((chrono.indice_der_tour) < (LINES - 11)){
            mvprintw(i + 1, x_milieu - 8 - 9, "Tour %d :", i + 1);
        }
        else{
            mvprintw(i + 1, x_milieu - 8 - 9, "Tour %d :", (chrono.indice_der_tour) - (LINES - 11) + i + 1);
        }
        formatAffichageGraphique(x_milieu, i + 1 , chrono.temps_tours[chrono.nb_tour - (i + 1)]);
    }

    /*On affiche les options*/
    afficher_options();
    refresh();
}

void afficher_flash(){
    int ligne, colonne, couleur;

    /*On efface tous les anciens objets graphiques de la fenêtre*/
    clear();

    /*Pour chacune des couleurs on affiche une serie de '*' */
    for (couleur = 0; couleur <= 8; couleur ++){

        for(ligne = 0; ligne < LINES; ligne++){

            for(colonne = 0; colonne < COLS ;colonne++){
                attron(COLOR_PAIR((couleur % 5) + 1));
                mvprintw(ligne, colonne, "*");
                attroff(COLOR_PAIR((couleur % 5) + 1));

            }
        refresh();
        usleep(10500); /*Temps de pause pour pas que cela paraisse figée sans mouvement*/
        }
    }
    clear();
}


int decalageDroite(int tab[], int val, unsigned int taille){
    int i;
    /*On s'assure que le tableau est pas nul*/
    assert(tab != NULL);

    /*Pour chaque valeur du tableau on prend sa valeur à côté*/
    for(i = taille - 1; i > 0; i--){
        tab[i] = tab[i - 1];
    }
    tab[0] = val;
    return 1;
}


void ajouter_tour(Chronometre *chrono){
    /*Si le nombre de tour est inférieur au nombre de lignes
    pouvant être affichée pour les tours marqués.
    */
    if((*chrono).nb_tour < (LINES - 11)){
        (*chrono).nb_tour ++;
    }

    (*chrono).indice_der_tour += 1;
    decalageDroite((*chrono).temps_tours, (*chrono).duree, (*chrono).nb_tour);
}


/*Cette partie du programme est une partie de tests*/

#if 0

int main(void){
    Chronometre chrono;

    /*Definition de l'écran et des couleurs*/
    initscr();
    curs_set(0);

    start_color();

    init_pair(1,COLOR_YELLOW, COLOR_BLACK);
    init_pair(2,COLOR_GREEN, COLOR_BLACK);
    init_pair(3,COLOR_RED, COLOR_BLACK);
    init_pair(4,COLOR_CYAN, COLOR_BLACK);
    init_pair(5,COLOR_WHITE, COLOR_BLACK);

    /*Si l'écran n'est pas aux normes erreur*/
    if((LINES < 14) || (COLS < 58)){
        printf("Taille de fenêtre insuffisante");
        exit(EXIT_FAILURE);
    }

    /*Initialisation du chrono*/
    chrono = initialiser_chronometre();

    /*Affichage de la durée du chrono*/
    afficher_duree(0, 0, chrono.duree);


    /*Affichage de l'interface et de l'avertisseur visuel*/
    afficher_interface(chrono);
    afficher_flash();

    /*Fin de programme*/
    getch();
    endwin();
    return 0;
}

#endif

