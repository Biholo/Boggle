#ifndef __LISTE__
#define __LISTE__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct __cell__{
    char c;
    struct __cell__ *suivant;
} Cellule_lettre, *Liste_lettre;


typedef struct __cell_find__{
    char * mot;
    struct __cell_find__ *suivant;
} Cellule_find, *Liste_find;


/**
 * @brief Alloue une Cellule_lettre avec le caractère en paramètre.
 * 
 * @param charactere (char) caractère à ajouter à la Cellule_lettre.
 * @return Cellule_lettre* 
 */
Cellule_lettre *alloue_cellule(char charactere);

/**
 * @brief Ajoute le caracètre à la Liste_lettre chainée en créant une nouvelle Cellule_lettre.
 * 
 * @param L (Liste_lettre*) Liste_lettre chainée de lettre.
 * @param charactere (char) caractère à ajouter.
 * 
 * @return Cellule_lettre* 
 */
Cellule_lettre *ajoute_cellule(Liste_lettre * L, char charactere);

/**
 * @brief Alloue une Cellule_lettre avec la chaine de  caractère en paramètre.
 * 
 * @param mot (char*) chaine à ajouter à la Cellule_lettre après l'allocation de la mémoire.
 * @return Cellule_lettre* 
 */
Cellule_find *alloue_cellule_find(char * mot);

/**
 * @brief Ajoute la chaine de caracètre à la Liste_lettre chainée en créant une nouvelle Cellule_lettre.
 * 
 * @param L (Liste_find*) Liste_lettre chainée de chaine de caractère.
 * @param mot (char*) chaine à ajouter à la Liste_lettre chainnée.
 * 
 * @return Cellule_lettre* 
 */
Cellule_find *ajoute_cellule_find(Liste_find * L, char * mot);

/**
 * @brief Supprimer les n derniers éléments de la Liste_lettre chainée.
 * 
 * @param n (int) Nombre d'élément à supprimer.
 * @param L (Liste_lettre*) Liste_lettre chainée de lettre (caractère).
  
*/
void suppression_liste(Liste_lettre * L, int n);

/**
 * @brief Concatène les lettres de la Liste_lettre chainée dans une variable. 
 * 
 * @param lettres (Liste_lettre) Liste_lettre chainée de lettre (caractère).
 * @return char* contaténation 
*/
void creer_mot(Liste_lettre lettres, char * mot);

/**
 * @brief Vérifie si le mot est dans la liste
 * 
 * @param L (Liste_find) Liste des mots trouvés
 * @param mot (char *) mot à chercher
 * @return 1 si présent si non 0 
*/
int recherche_mot_liste(Liste_find L, char * mot);
#endif
