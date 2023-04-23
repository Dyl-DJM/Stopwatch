/*PremPart.h*/

#ifndef __PREMPART__
#define __PREMPART__

    /*Definition de la structure de temps*/
    struct timeval temps_debut, temps_fin;

    /*Cette fonction renvoie la valeur de l'intervalle de temps en ms entre
    'debut' et 'fin'*/
    int intervalle_ms(struct timeval debut, struct timeval fin);

    /*Cette fonction renvoie la valeur de conversion d'une durée 'nb_ms' en ms à une
    durée en centième de secondes*/
    int nb_ms_vers_centiemes(int nb_ms);

    /*Cette fonction renvoie la valeur de conversion d'une durée 'nb_ms' en ms à une
    durée en secondes*/
    int nb_ms_vers_secondes(int nb_ms);

    /*Cette fonction renvoie la valeur de conversion d'une durée 'nb_ms' en ms à une
    durée en minutes*/
    int nb_ms_vers_minutes(int nb_ms);

    /*Cette fonction renvoie la valeur de conversion d'une durée 'nb_ms' en ms à une
    durée en heures*/
    int nb_ms_vers_heures(int nb_ms);

#endif



