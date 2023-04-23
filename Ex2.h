/* Ex2.h */
#ifndef __EX2__
#define __EX2__
#include "PremPart.h"
#include "ChronoMoyen.h"

    /*On definit une macro*/
    #define NB_TEMPS 100

    /*Definition de la structure Chronometre constituée de :

     - l'état
     - chronometre
     - alarme
     - indice du dernier tour enregistré
     - nombre de tours marqués
     - Tours marqués

    */
    typedef struct{
    unsigned char etat;
    int duree;
    int avertissement;
    int indice_der_tour;
    int nb_tour;
    int temps_tours[NB_TEMPS];

    }Chronometre;

    /*Cette fonction renvoie un chronometre définit par la structure
    précemment.
    Les champs de la structure sont initilisés à leur valeurs de départ*/
    Chronometre initialiser_chronometre();

    /*Cette fonction permet l'affichage gaphique des différentes options
    de l'application*/
    void afficher_options();

    /*Cette fonction permet l'affichage graphique du chronomètre 'chrono' ainsi que des
    tours marqués par l'utilisateur et l'alarme prédéfinie*/
    void afficher_interface(Chronometre chrono);

    /*Cette fonction permet l'alerte visuelle graphique permettant de prévenir
    l'utilisateur*/
    void afficher_flash();

    /*Cette fonction renvoie 1 après avoir décalé le tableau 'tab[]' de taille 'taille' vers la droite
    en ajoutant la valeur 'val' un temps en ms en première position du tableau
    */
    int decalageDroite(int tab[], int val, unsigned int taille);

    /*Cette fonction permet l'ajout d'un tour marqué par l'utilisateur dans le chronomètre '*chrono'
    la structure est ainsi directement modifiée.
    */
    void ajouter_tour(Chronometre *chrono);

#endif
