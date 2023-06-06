#include <time.h>

#include "../include/Affichage.h"
#include "../include/Game.h"
#include "../include/Mots.h"

int main(void) {
    srand(time(NULL));
    //Initialisation des variables
    MEVENT ev;
    int touche;
    ArbreLexico A = NULL;
        
    cree_arbre("Mots", &A);
    Game jeu;
    int row, col;
    
    initscr();
    start_color();
    //Initialisation des couleurs
    init_pair(1, COLOR_BLACK, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_RED, COLOR_RED);

    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, FALSE);
    curs_set(FALSE);
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);

//Détermination de la taille du plateau par l'utilisateur
    mvprintw(0, 0, "Veuillez entrer le nombre de column (maximun 25):");
    col = getDimension(25);
    mvprintw(0, 0, "Veuillez entrer le nombre de ligne (maximun 10):");
    row = getDimension(10);
    noecho();
    
    //Génération et affichage du plateau
    generation_plateau(&jeu, col, row);
    afficher_jeu(jeu);

//Tant que le nombre de vie n'est pas 0 le jeu continue
    while (jeu.life != 0) {
        touche = getch();
        if (touche == KEY_MOUSE && getmouse(&ev) == OK) {
            clic_case(&jeu, ev.x, ev.y);
        }else {
            selection_clavier(&jeu, A,touche);
        }
        afficher_jeu(jeu);
    }
    game_over(jeu);
    refresh();
    getch();
    endwin();


    libere(&A);

    return 0;
}
