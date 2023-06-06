#include "../include/Mots.h"

#define MAX_LETTRES 512

/*Allocation d’un nœud*/
NoeudLexico * alloue_noeud(char c){
    NoeudLexico * a = (NoeudLexico *)malloc(sizeof(NoeudLexico));
    if(a == NULL)
        fprintf( stderr, "Erreur d'allouer\n");
    a->c = c;
    a->filsG = NULL;
    a->frereD = NULL;
    return a;
}

/*insere le mot une lettre par une lettre*/
int insere(ArbreLexico *A, char *mot){
    if(*A == NULL && *mot == '\0') {/*si A est vide et c'est la fin de le mot, on allouer une noeud*/
        *A = alloue_noeud(*mot);
        return 1;/*le mot est dans arbre */
    }
    else if(*A == NULL) { /*si A est vide, et c'est pas la fin de mot*/
        *A = alloue_noeud(*mot);/*allouer le noued pour lettre*/
        insere(&(*A)->filsG, mot+1);/*insere le suivant lettre*/
        return 1;
    }
    else if((*A)->c == *mot) {/*si cette lettre est pareil , on regarde suivant lettre dans le mot si il est pareille avec le filsg de ce noued*/
        insere(&(*A)->filsG, mot+1);
        return 1;
    }
    else if((*A)->c > *mot) {/*si cette lettre est plus petite que le noued->c, on alloue une lettre a cote de ce noued*/
        NoeudLexico * tmp = alloue_noeud(*mot);
        tmp->frereD = *A;
        *A = tmp;
        insere(&(*A)->filsG, mot+1);/*on regarde la lettre suivant*/
        return 1;
    }
    else {/*sinon, la lettre de ce mot est plus grand que le noued->c, on l'ajoute a droit*/
        insere(&(*A)->frereD, mot);
        return 1;
    }
    return 0;
}

void libere(ArbreLexico *A){
    if(*A) {
        libere(&((*A)->filsG));
        libere(&((*A)->frereD));
        free(*A);
        *A = NULL;
    }
}

/*Recherche un mot dans l'arbre*/
int recherche(ArbreLexico A, char *mot){
    if(A == NULL){
        return 0; // si l'arbre est vide, le mot n'existe pas
    }
    if(A->c == *mot) {
        if(*mot == '\0')
            return 1; // si on a atteint la fin du mot, le mot existe dans l'arbre
        return recherche(A->filsG, mot+1); // sinon on continue la recherche dans le sous-arbre gauche
    }
    if(A->c < *mot) {
        return recherche(A->frereD, mot); // on recherche dans le sous-arbre droit si la lettre est plus petite
    } else {
        return 0; // si la lettre est plus grande, le mot n'existe pas dans l'arbre
    }
}

/* Création de l'arbre à partir du nom d'un fichier*/
int cree_arbre(char *nom, ArbreLexico *A){
    FILE *f = NULL;
    char *chaine = (char *) malloc( 512 );
    const char *separateurs = " \n";
    char *strtoken;
    f = fopen(nom, "r");
    if(f == NULL){
        printf("Le fichier %s ne peut pas être ouvert", nom);
        fclose(f);
        return 0;
    }else{
        int nb = 0;
        while(!feof(f)){
            fgets(chaine, 512, f);
            strtoken = strtok(chaine, separateurs);

            while ( strtoken != NULL ){
                strtoken[strlen(strtoken)-1] = '\0';/*parce que strtoken[strlen(strtoken)-1] = '\r'*/
                nb += insere(A, strtoken);
                // On demande le token suivant.
                strtoken = strtok ( NULL, separateurs );
            }
        }
        fclose(f);
        free(chaine);
        return 1;
    }
}