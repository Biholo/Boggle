#include "../include/Affichage.h"
#include "../include/Game.h"

/*Permet d'afficher */
void affiche_case(char *caract, int order, Coordonnees coord) {
    int selected = 2;
    if(order > 0){
        selected = 1;
    }
    attron(COLOR_PAIR(selected));
    for(int i = coord.y * 3; i < 3 + coord.y * 3; i++){
        for(int j = 0 + coord.x * 5; j < 5 + coord.x * 5; j++){
            /*Si on est au centre de la case on affiche la lettre*/
            if( i == 1 + coord.y * 3 && j == 2 + coord.x * 5) {
                mvprintw(i, j, "%s", caract);
            }
            /*Si on est à la case bas droite et que la case est selected, on affiche l'occurence de sélection*/
            else if(i == 2 + coord.y * 3 && j == 4 + coord.x * 5 && order != 0){
                mvprintw(i,j, "%d", order);
            }
            else {
                mvprintw(i,j, " ");
            }
        }
    }
    attroff(COLOR_PAIR(selected));
}

/*Affiche l'emplacement du curseur sur le plateau*/
void affiche_cursor(Coordonnees c){
    int x = ((c.x + 1) * 5 ) - 1;
    int y = c.y * 3;
    attron(COLOR_PAIR(3));
    mvprintw(y, x, " ");
    attroff(COLOR_PAIR(3));
}

/*Affiche le mot en cours de formation*/
void afficher_mot(Liste_lettre L, int largeur){
    int i = 0;
    mvprintw(0, largeur * 5 + 5, "Sélection actuelle:");
    mvprintw(1, largeur * 5 + 5, "->");

    while(L != NULL){
        mvprintw(1, largeur * 5 + 7 + i, "%c", L->c);
        L = L->suivant;
        i++;
    }
}

/*Interface vie, score & mots trouvé*/
void affichage_score_mot(int hauteur, int score, int vie){
    mvprintw(hauteur * 3 + 1, 0, "Vie: %d", vie);
    mvprintw(hauteur * 3 + 2, 0, "Votre score: %d", score);
    mvprintw(hauteur * 3 + 3, 0, "Liste_lettre des mots trouve:");
}

/*Affiche si un message si une case n'est pas valide à la sélection*/
void afficher_non_valide(int largeur){
    mvprintw(3, largeur * 5 + 5, "Attention !");
    mvprintw(4, largeur * 5 + 5, "La case que vous venez de sélectionner n'est pas adjacente.");
}

/*Affiche un message si le mot n'est pas valide*/
void afficher_mot_non_valide(int largeur){
    mvprintw(3, largeur * 5 + 5, "Attention !");
    mvprintw(4, largeur * 5 + 5, "Le mot que vous venez de composer n'est pas valide!");
}

/*Supprime l'affichage du mot en formation*/
void suppression_affichage_mot(int largeur){
    mvprintw(1, largeur * 5 + 7, "                                    ");
    refresh();
}

/*Masque la notification d'erreur*/
void masque_notif_erreur(int largeur){
    mvprintw(3, largeur * 5 + 5, "                                  ");
    mvprintw(4, largeur * 5 + 5, "                                                                                 ");
    refresh();
}

/*Affiche la liste des mots trouvés*/
void afficher_mot_trouve(Liste_find L, int hauteur){
    int i  = 0;
    while(L != NULL){
        mvprintw(hauteur * 3 + 4 + i, 0, "%s", L->mot);
        L = L->suivant;
        i++;
    }
}

/*Affichage du jeu dans sa globalité*/
void afficher_jeu(Game jeu){
    /*Affichage cases*/
    for(int i = 0; i < jeu.dimenssion.y; i++){
        for(int j = 0; j < jeu.dimenssion.x; j++){
            affiche_case(&(jeu.plateau[i][j].lettre), jeu.plateau[i][j].order_selection, jeu.plateau[i][j].coordonnees);
        }
    }
    affichage_score_mot(jeu.dimenssion.y, jeu.score, jeu.life);
    affiche_cursor(jeu.cursor);
    afficher_mot_trouve(jeu.Mots, jeu.dimenssion.y);
    afficher_mot(jeu.Lettres, jeu.dimenssion.x);
    refresh();
}

/*Affichage de fin de partie*/
void game_over(Game jeu){
    clear();
    mvprintw((jeu.dimenssion.y * 3) / 2, (jeu.dimenssion.x * 5) / 2, "Game Over");
    mvprintw((jeu.dimenssion.y * 3) / 2 + 1, (jeu.dimenssion.x * 5) / 2 - 5, "Votre Score est de %d", jeu.score);


}