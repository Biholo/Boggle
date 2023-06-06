#include "../include/Game.h"
#include "../include/Liste.h"
#include "../include/Affichage.h"
#include "../include/Mots.h"

/* Génération de lettre celon des probabilités d'appartion*/
void generation_lettre(char *c) {
    int tab[26] = {11, 19, 26, 33, 40, 47, 54, 60, 65, 69, 73, 76, 79, 82, 84, 86, 88, 90, 92, 94, 95, 96, 97, 98, 99, 100};
    char * lettres = "ETAINOSRHDLCMUBFGPWYJKQBXZ";
    int number = rand() % 100;
    for(int i = 0; i < 26; i++) {
        if(number <= tab[i]){
            (*c) = lettres[i];
            break;
        }
    }
}

/* Genere un plateau (partie de jeu)*/
void generation_plateau(Game * g, int largeur, int hauteur){
    /*Allocation de la mémoire pour générer le plateau*/
    g->plateau = (struct Case**)malloc(hauteur * sizeof(struct Case*));
    for(int  i = 0; i < hauteur; i++){
        g->plateau[i] = (struct Case*)malloc(largeur * sizeof(struct Case));
    }
    /* Génération de toutes les lettres pour chaque case*/
    for(int j = 0; j < hauteur; j++){
        for(int i = 0; i < largeur; i++){
            generation_lettre(&(g->plateau[j][i].lettre));
            g->plateau[j][i].order_selection = 0;
            g->plateau[j][i].coordonnees.x = i;
            g->plateau[j][i].coordonnees.y = j;
        }
    }
    /* On initialise toutes les variables du jeu*/
    g->Lettres = NULL;
    g->Mots = NULL;
    g->taille_word = 0;
    g->score = 0;
    g->life = 3;
    g->dimenssion.y = hauteur;
    g->dimenssion.x = largeur;
    g->cursor.y = 0;
    g->cursor.x = 0;
    g->last_case.x = -1;
    g->last_case.y = -1;

}
/* Return 1 si la case de coordonnée x et y est adjacente à la case du curseur*/
int est_adjacent(Coordonnees c, int x, int y) {
    if(abs(c.x - x) <= 1 && abs(c.y - y) <= 1)
        return 1;
    return 0;
}


int verifier_case(Game * g, int case_x, int case_y) {
    /* Si la case n'est pas déjà sélectionné et adjacent à la dernière case sélectionné*/
    if( g->plateau[case_y][case_x].order_selection == 0 && (est_adjacent(g->last_case, case_x, case_y) || g->taille_word == 0)){ // n'importe quel clic si jeu vide.
        return 1;
    }
    /*si la case est déjà sélectionné.*/
    else if(g->plateau[case_y][case_x].order_selection != 0) {
        return 2;
    }
    return 0;

}

/*Recherche la dernière case sélectionné. (utilise lors de la suppression de case sélectionné)*/
void search_last_case(Coordonnees * coord, Game g){
    for(int j = 0; j < g.dimenssion.y; j++){
        for(int i = 0; i < g.dimenssion.x; i++){
            /*La denrnière case "sélectionné" est la case ayant le plus grand "order_selection"*/
            if(g.taille_word == g.plateau[j][i].order_selection){
                coord->x = i;
                coord->y = j;
            }
        }
    }
}

/* Modification la case*/
void change_case(Game * g, int case_x, int case_y) {
    /*Verification que la case ne soit pas déjà sélectionné, et que la case soit une case annexe*/
    if(verifier_case(g, case_x, case_y) == 1){ // n'importe quel clic si jeu vide.
        g->taille_word++;
        g->plateau[case_y][case_x].order_selection = g->taille_word;
        /*Ajout de la lettre à la Liste_lettre chainée*/
        ajoute_cellule(&(g->Lettres), g->plateau[case_y][case_x].lettre);

        /*Modification de l'emplcacement du curseur et de la dernière case sélectionné.*/
        g->cursor.x = case_x;
        g->cursor.y = case_y;
        g->last_case.x = case_x;
        g->last_case.y = case_y;
    }

    /*Si on clique sur une case déjà selectionner on la désélectionne*/
    else if(verifier_case(g, case_x, case_y) == 2){
        int suppr = 0;
        /*supression des cases ayant été sélectionné après cette case*/
        for(int i = 0; i < g->dimenssion.y; i ++){
            for(int j = 0; j < g->dimenssion.x; j++){
                if(g->plateau[i][j].order_selection > g->plateau[case_y][case_x].order_selection) {
                    g->plateau[i][j].order_selection = 0;
                    suppr++;
                }
            }
        }
        g->plateau[case_y][case_x].order_selection = 0;
        suppr++;
        /*Supression et modification des variables*/
        suppression_liste(&(g->Lettres),suppr);
        suppression_affichage_mot(g->dimenssion.x);
        g->taille_word = g->taille_word - suppr;
        g->cursor.x = case_x;
        g->cursor.y = case_y;
        /*On doit trouvé la case ayant le plus grand ordre de sélection*/
        search_last_case(&(g->last_case), *g);
    }
    else if(verifier_case(g, case_x, case_y) == 0)
        afficher_non_valide(g->dimenssion.x);
}


/* Transforme le clic souris en une case*/
void clic_case(Game *g, int x, int y) {
    int case_x = x / 5;
    int case_y = y / 3;

    /*Verification que le clic soit bien sur le plateau*/
    if(case_x <= g->dimenssion.x && case_y <= g->dimenssion.y ){
        change_case(g, case_x, case_y);
    }
}

/*Calcul le score d'un mot*/
int calcul_score(char *mot) {
    double len = strlen(mot);
    double temp = pow(2.0, len - 3.0);
    int score = (int)temp;     /*convertion en int*/
    return score;
}

/*Remet toutes les cases en positio initial lors de la validation d'une chaine de caractère*/
void refresh_selection(Game *g){
    for(int j = 0; j < g->dimenssion.y; j++){
        for(int i = 0; i < g->dimenssion.x; i++){
            if(g->plateau[j][i].order_selection != 0){
                g->plateau[j][i].order_selection = 0;
            }
        }
    }
    /* -1 lorsque il n'y a pas de last case*/
    g->last_case.x = -1;
    g->last_case.y = -1;
}


void selection_clavier(Game *g, ArbreLexico A,int touche){/*si on appyer enter, on finit le mot et on le verifier*/
    char mot[100];
    switch (touche)
    {
    /*Variables de déplacement du curseur:*/
    case KEY_UP:
        if(g->cursor.y - 1 >= 0)
            g->cursor.y--;
        break;

    case KEY_DOWN:
        if(g->cursor.y + 1 < g->dimenssion.y)
            g->cursor.y++;

        break;
    case KEY_LEFT:
        if(g->cursor.x - 1 >= 0)
            g->cursor.x--;

        break;
    case KEY_RIGHT:
        if(g->cursor.x + 1 < g->dimenssion.x)
            g->cursor.x++;
        break;

    case '\n':
        /*Validation d'un mot*/
        creer_mot(g->Lettres, mot);
        /*vérification de l'existance du mot*/
        if(recherche(A, mot) && !recherche_mot_liste(g->Mots, mot)){
            ajoute_cellule_find(&(g->Mots), mot);
            g->score += calcul_score(mot);
        }else{
            g->life--;
            afficher_mot_non_valide(g->dimenssion.x);
        }
        /*Supression des lettres de la Liste_lettre chainée et on remet le plateau à 0*/
        suppression_liste(&(g->Lettres), g->taille_word);
        refresh_selection(g);
        suppression_affichage_mot(g->dimenssion.x);
        g->taille_word = 0;
        break;

    case ' ':
        /*Validation d'une case*/
        masque_notif_erreur(g->dimenssion.x);
        change_case(g, g->cursor.x, g->cursor.y);
        break;

    default:
        break;
    }
}

int getDimension(int max) {
    int num;
    char buffer[256];

    do {
        refresh(); 
        mvscanw(2, 0, "%s", buffer);
        /*sscanf permet de controler que l'utilisteur entre bien un nombre*/
        if (sscanf(buffer, "%d", &num) != 1 || num > max) {
            mvprintw(2, 0, "       ");
            mvprintw(1, 0, "Le nombre n'est pas valide, il doit être strictementinférieur à %d. Entrez à nouveau : ", max);
            refresh(); 
        }
    } while (num > max);
    clear(); 

    return num;
}