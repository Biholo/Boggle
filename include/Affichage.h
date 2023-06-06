#ifndef __AFFICHAGE__
#define __AFFICHAGE__

#include <ncurses.h>
#include <stdio.h>
#include <ctype.h>

#include "Game.h"

/**
 * @brief Affiche une case.
 * 
 * @param caract (char*) caractère à afficher.
 * @param order (int) ordre de séletion de la case.
 * @param coord (Coordonnees) coordonnées de la case à afficher.
 */
void affiche_case(char *caract, int order, Coordonnees coord);

/**
 * @brief Affiche une notification indiquant que la case ne peut pas être sélectionné.
 * 
 * @param largeur (int) 
 */
void afficher_non_valide(int largeur);


/**
 * @brief Affiche une notification indiquant que le mot n'est pas valide
 * 
 * @param largeur (int) 
 */
void afficher_mot_non_valide(int largeur);

/**
 * @brief Supprimer l'affichage du mot en formation
 * 
 * @param largeur (int) 
 */
void suppression_affichage_mot(int largeur);

/**
 * @brief Masque les notifications qui sont affiché lors de la partie.
 * 
 * @param largeur (int) 
 */
void masque_notif_erreur(int largeur);

/**
 * @brief Affiche le plateau ainsi que les mots trouvées, le curseur, le score 
 * et le mot qui est en train d'être formé.
 * 
 * @param jeu (Game)
 */
void afficher_jeu(Game jeu);

/**
 * @brief Affiche l'interface de défaite.
 * 
 * @param jeu (Game)
 */
void game_over(Game jeu);

#endif
