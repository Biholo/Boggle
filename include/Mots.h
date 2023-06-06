#ifndef __MOT__
#define __MOT__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct noeud{
    char c;
    struct noeud *filsG, *frereD;
} NoeudLexico, *ArbreLexico;


/**
 * @brief Alloue un noeud de NoeudLexico
 * 
 * @param c (char) 
 * @return NoeudLexico
 */
NoeudLexico * alloue_noeud(char c);

/**
 * @brief Insère le mot en paramètre lettre par lettre dans l'arbre lexico
 * 
 * @param A (ArbreLexico*)
 * @param mot (char*) 
 * @return (int) 
 */
int insere(ArbreLexico *A, char *mot);

/**
 * @brief Libère l'arbre lexico
 * 
 * @param A (ArbreLexico*)
 */
void libere(ArbreLexico *A);

/**
 * @brief Véririfie si le mot est présent dans l'arbre lexico.
 * 
 * @param A (ArbreLexico*)
 * @param mot (char*) 
 * @return (int) 1 si le mot est présent et 0 dans le cas contraire
 */
int recherche(ArbreLexico A, char *mot);

/**
 * @brief Crée l'arbre à partir des mots contenue dans le fichier nom en paramètre.
 * 
 * @param nom (char*) Nom du fichier à ouvrir.
 * @param A (ArbreLexico*)
 * @return (int) 1 si le mot est présent et 0 dans le cas contraire
 */
int cree_arbre(char *nom, ArbreLexico *A);

#endif
