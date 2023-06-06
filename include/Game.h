#ifndef __GAME__
#define __GAME__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include <ctype.h>
#include <math.h>

#include "Mots.h"
#include "Liste.h"

typedef struct Coordonnees {
    int x;
    int y;
}Coordonnees;

typedef struct Case {
    Coordonnees coordonnees;
    char lettre;
    int order_selection;
}Case;

typedef struct  Game{
    struct Case ** plateau;
    Coordonnees dimenssion;
    Liste_lettre Lettres;
    Liste_find Mots;
    Coordonnees cursor;
    Coordonnees last_case;
    int taille_word;
    int score;
    int life;
} Game;

/**
 * @brief Génère un caractère aléatoire celon un taux d'apparition 
 * pour chaque lettre.
 * 
 * @param c (char*), pointeur vers un caractère
 */
void generation_lettre(char *c);

/**
 * @brief Initialise une partie de jeu dans la structure Game d'un plateau de coordonnée connue.
 * 
 * @param g (Game*)
 * @param largeur (int) Largeur du plateau
 * @param hauteur (int) Hauteur du plateau
 */
void generation_plateau(Game * g, int largeur, int hauteur);

/**
 * @brief Vérifie que les coordonnées x et y forment une case adjacente à la dernière case validé.
 * 
 * @param c (Coordonnees)
 * @param x (int) Coordonnée x d'une case
 * @param y (int) Coordonnée y d'une case
 * @return (int) 1 si la case est "valide" et 0 dans le cas contraire.
 */
int est_adjacent(Coordonnees c, int x, int y);

/**
 * @brief Vérifie l'état (order_selection) de la case qui a pour coordonnée x et y.
 * 
 * @param g (Game)
 * @param case_x(int) Coordonnée x d'une case
 * @param case_y (int) Coordonnée y d'une case
 * @return (int) 1 si la case n'est pas encore sélectionné, 2 si la case est déjà sélectionné
 * et 0 si non.
 */
int verifier_case(Game * g, int case_x, int case_y);

/**
 * @brief Le jeu change l'état de la case séléctionné et apporte les modification
 * nécessaire au jeu. Si la case est validé par les différentres fonction alors
 * la lettre est ajouté à la Liste_lettre chainée des lettres. Dans le cas contraire
 * affiche que la case n'est pas valide.
 * 
 * @param g (Game *)
 * @param case_x (int) Coordonnée x d'une case
 * @param case_y (int) Coordonnée y d'une case
 */
void change_case(Game * g, int case_x, int case_y) ;


/**
 * @brief Change une case à partir des coordonnées venant d'un clic souris.
 * 
 * @param g (Game *)
 * @param x (int) Coordonnée x d'un clic dans la fenêtre 
 * @param y (int) Coordonnée y d'un clic dans la fenêtre
 */
void clic_case(Game *g, int x, int y);

/**
 * @brief Modifie toutes les valeurs du champ order_selection à 0.
 * 
 * @param g (Game *)
 */
void refresh_selection(Game *g);

/**
 * @brief Calcul le score à partir d'un mot.
 * 
 * @param mot (char *)
 * @return (int) Le score du mot.
 */
int calcul_score(char * mot);



/**
 * @brief Modifie g (partie de jeu) en fonction de la touche sélectioner.
 * Modifie l'Coordonnees du curseur si une flèche directionnelle est sélectionné.
 * Si touche est ' ' change case, si '\n' processus de vérification du mot et modification du
 * jeu.
 * 
 * 
 * @param g (Game *)
 * @param A (ArbreLexico)
 * @param touche (int)
 */
void selection_clavier(Game *g, ArbreLexico A,int touche);


int getDimension(int max);

#endif
