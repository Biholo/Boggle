#include "../include/Liste.h"

Cellule_lettre *alloue_cellule(char charactere) {
    // Allouer une nouvelle Cellule_lettre
    Cellule_lettre *let = (Cellule_lettre *)malloc(sizeof(Cellule_lettre));
    if (let == NULL) {
        fprintf(stderr, "Erreur : impossible d'allouer de la mémoire pour Cellule_lettre.\n");
        return NULL;
    }

    let->c = charactere;
    let->suivant = NULL;
    return let;
}

Cellule_lettre *ajoute_cellule(Liste_lettre * L, char charactere) {
    if(*L == NULL){
        *L = alloue_cellule(charactere);
        return *L;
    }else {/*sinon on l'ajoute a la fin de la Liste_lettre*/
        return ajoute_cellule(&(*L)->suivant, charactere);
    }
}

Cellule_find *alloue_cellule_find(char * mot) {
    // Allouer une nouvelle Cellule
    Cellule_find *let = (Cellule_find *)malloc(sizeof(Cellule_find));
    if (let == NULL) {
        fprintf(stderr, "Erreur : impossible d'allouer de la mémoire pour Cellule.\n");
        return NULL;
    }

    let->mot = malloc((strlen(mot) + 1) * sizeof(char));

    if (let->mot == NULL) {
        fprintf(stderr, "Erreur : impossible d'allouer de la mémoire pour la chainde de caractère de la Cellule.\n");
        return NULL;
    }
    strcpy(let->mot, mot);
    let->suivant = NULL;
    return let;
}

Cellule_find *ajoute_cellule_find(Liste_find * L, char * mot) {
    if(*L == NULL){
        *L = alloue_cellule_find(mot);
        return *L;
    }else {/*sinon on l'ajoute a la fin de la liste*/
        return ajoute_cellule_find(&(*L)->suivant, mot);
    }
}

/*Suppresion des n derniers éléments de la Liste_lettre*/
void suppression_liste(Liste_lettre * L, int n){
    if(*L == NULL)
        return;
    /*On cherche la longeur de la Liste_lettre*/
    int len = 0;
    Liste_lettre current = *L;
    while (current != NULL) {
        len++;
        current = current->suivant;
    }

    /*on cherche le n élément à partir de la fin */
    int x = len - n;
    if (x <= 0) {
        /*supression des éléments de la Liste_lettre*/
        while (*L != NULL) {
            Liste_lettre temp = *L;
            *L = (*L)->suivant;
            free(temp);
        }
    } else {
        /*parcours jusqu'au n eme éléments de la fin*/
        current = *L;
        for (int i = 1; i < x; i++) {
            current = current->suivant;
        }

        /*à partir du n éléments on supprime les cellules*/
        while (current->suivant != NULL) {
            Liste_lettre temp = current->suivant;
            current->suivant = temp->suivant;
            free(temp);
        }
    }
}
/*Creéation d'un mot à partir d'une Liste_lettre chainé de lettre*/
void creer_mot(Liste_lettre lettres, char * mot) {
    char * mot_temp = (char *) malloc( 512 );
    int len = 0;
    for(; lettres; lettres = lettres->suivant) {
        mot_temp[len++] = tolower(lettres->c);
    }
    mot_temp[len] = '\0';
    strcpy(mot, mot_temp);
}
/* Vérifie si un mot est dans la liste*/
int recherche_mot_liste(Liste_find L, char * mot){
    for(; L; L = L->suivant) {
        if(strcmp(L->mot, mot) == 0)
            return 1;
    }
    return 0;
}