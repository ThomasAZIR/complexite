#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
// Fonction pour echanger deux entiers
void echange(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


// Fonction qui affiche un tableau de taille n
void affiche(int *t, int n) {
    int i;

    for (i = 0; i < n; ++i)
        printf("%d ", t[i]);
    printf("\n");
}

// Structure representant une experience
// Un marqueur est un entier compris entre 0 et m
typedef struct {
    int m; // Nombre de marqueurs
    int *marqueurs; // Tous les marqueurs

    int p; // Nombre de marqueurs positifs
    int *marqueurs_positifs; // Les marqueurs positifs
} EXPERIENCE;

// Fonction qui cree une expérience et la stocke dans la structure passee en parametre
// Attention : il faut que p <= m
void cree_experience(EXPERIENCE *xp, int p, int m) {
    int i, j;

    xp->m = m;

    xp->marqueurs = (int *) malloc(m * sizeof(int));
    for (i = 0; i < m; ++i)
        xp->marqueurs[i] = i;

    // On melange les marqueurs dans l'ensemble des marqueurs par l'algorithme de Fisher-Yates
    for (i = m - 1; i >= 0; --i) {
        j = rand() % (i + 1);
        echange(&xp->marqueurs[i], &xp->marqueurs[j]);
    }

    // On choisit p marqueurs parmi les m qui seront les marqueurs positifs
    int *tmp = (int *) malloc(m * sizeof(int));
    for (i = 0; i < m; ++i)
        tmp[i] = i;

    xp->p = p;

    xp->marqueurs_positifs = (int *) malloc(p * sizeof(int));
    for (int i = 0; i < p; ++i) {
        j = rand() % (m - i);
        xp->marqueurs_positifs[i] = xp->marqueurs[tmp[j]];
        tmp[j] = tmp[m - i - 1];
    }

    free(tmp);
}

// Algorithme de tri fusion
// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    /* create temp arrays */
    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
     are any */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
     are any */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/* l is for left index and r is right index of the
 sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

// Fonction qui libere la memoire dans une experience
void libere_experience(EXPERIENCE *xp) {
    free(xp->marqueurs);
    free(xp->marqueurs_positifs);
}

// Fonction a completer - Strategie 1
// Le second argument servira a compter le nombre d'utilisation de l'opérateur OP
// Fonction a completer - Strategie 1
// Le second argument servira a compter le nombre d'utilisation de l'opérateur OP
int *marqueurs_negatifs1(EXPERIENCE *xp, int *cptOP) {

    *cptOP = 0;
    int n = xp->m;
    int npos = xp->p;
//    int *tabRes[xp->m - xp->p];
    int *res = (int *) malloc((xp->m - xp->p) * sizeof(int)); // le nombre de marqueurs négatifs
    int indent = 0;

    for (int i = 0; i < n; i++) {
        int bool = 1; //Valeur qui va décider si on rajoute le marqueurs ou pas
        for (int j = 0; j < npos; j++) {
            if (xp->marqueurs[i] == xp->marqueurs_positifs[j]) {
                bool = 0;
            }
            *cptOP += 1;
        }
        if (bool == 1) {
            res[indent] = xp->marqueurs[i];
            indent += 1;
        }
    }

//    affiche(tabRes, xp->m - xp->p);
    return res;
}

// Fonction a completer - Strategie 2
// Le second argument servira a compter le nombre d'utilisation de l'opérateur OP
int *marqueurs_negatifs2(EXPERIENCE *xp, int *cptOP) {
    *cptOP = 0;
    int *res = (int *) malloc((xp->m - xp->p) * sizeof(int));
//    int n = xp->m;
//    int npos = xp->p;
//
//    //Triage du tableau des marqueurs positifs
//    for (int i = 0; i < npos; i++) {
//        for (int j = 0; j < npos - i; j++) {
//            if (xp->marqueurs_positifs[j] > xp->marqueurs_positifs[j + 1]) {
//                int passage = xp->marqueurs_positifs[j];
//                xp->marqueurs_positifs[j] = xp->marqueurs_positifs[j + 1];
//                xp->marqueurs_positifs[j + 1] = passage;
//            }
//        }
//    }
//    //verification des marqueurs triés
//    printf("Marqueurs positifs triés : ");
//    for (int i = 0; i < npos; i++) {
//        printf(" %d", xp->marqueurs_positifs[i]);
//    }
//    printf("\n");
//
//    // Determination des marqueurs negatifs
//    for (int i = 0; i < n; i++) {
//
//    }


    mergeSort(xp->marqueurs_positifs, 0, xp->p - 1);
    printf("Marqueurs positifs tries\n");
    affiche(xp->marqueurs_positifs, xp->p);

    int n = 0;

    for (int i = 0; i < xp->m - 1; i++) {
        int val = xp->marqueurs[i];
        int inf = 0;
        int sup = xp->p - 1;
        int mid;
        int x = 0;
        while ((inf <= sup) && (x == 0)) {
            mid = (sup + inf) / 2;
            if (val < xp->marqueurs_positifs[mid]) {
                sup = mid - 1;
            } else if (val > xp->marqueurs_positifs[mid]) {
                inf = mid + 1;
            } else {
                x = 1;
            }
            *cptOP += 1;
        }
        if (x != 1) {
            res[n] = xp->marqueurs[i];
            n++;
        }
    }

    return res;
}

// Fonction a completer - Strategie 3
// Le second argument servira a compter le nombre d'utilisation de l'opérateur OP
int *marqueurs_negatifs3(EXPERIENCE *xp, int *cptOP) {
    *cptOP = 0;
    int *res = (int *) malloc((xp->m - xp->p) * sizeof(int));
    int n = xp->m;
    int npos = xp->p;
    int indentRecherche = 0;
    int indentAjout = 0;

    //Triage manuel

//    //Triage du tableau des marqueurs positifs
//    for (int i = 0; i < npos; i++) {
//        for (int j = 0; j < npos - i; j++) {
//            if (xp->marqueurs_positifs[j] > xp->marqueurs_positifs[j + 1]) {
//                int passage = xp->marqueurs_positifs[j];
//                xp->marqueurs_positifs[j] = xp->marqueurs_positifs[j + 1];
//                xp->marqueurs_positifs[j + 1] = passage;
//            }
//        }
//    }
//    //verification des marqueurs positifs triés
//    printf("Marqueurs positifs triés : ");
//    for (int i = 0; i < npos; i++) {
//        printf(" %d", xp->marqueurs_positifs[i]);
//    }
//    printf("\n");
//
//    //Triage du tableau des marqueurs
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n - i; j++) {
//            if (xp->marqueurs[j] > xp->marqueurs[j + 1]) {
//                int passage = xp->marqueurs[j];
//                xp->marqueurs[j] = xp->marqueurs[j + 1];
//                xp->marqueurs[j + 1] = passage;
//            }
//        }
//    }
//    //verification des marqueurs triés
//    printf("Marqueurs triés : ");
//    for (int i = 0; i < n; i++) {
//        printf(" %d", xp->marqueurs[i]);
//    }
//    printf("\n");

    //determination des marqueurs négatifs



    mergeSort(xp->marqueurs_positifs, 0, xp->p - 1);
    printf("Marqueurs positifs triés\n");
    affiche(xp->marqueurs_positifs, xp->p);

    mergeSort(xp->marqueurs, 0, xp->m - 1);
    printf("Marqueurs triés\n");
    affiche(xp->marqueurs, xp->m);

    for (int i = 0; i < n; i++) {
        if (xp->marqueurs[i] == xp->marqueurs_positifs[indentRecherche]) {
            indentRecherche += 1;
        } else {
            res[indentAjout] = xp->marqueurs[i];
            indentAjout += 1;
        }
        *cptOP += 1;
    }
    return res;
}

void test(int p, int m) {
    EXPERIENCE xp;
    int cpt, *marqueurs_negatifs;

    // Creation de l'experience
    cree_experience(&xp, p, m);

    printf("Marqueurs :\n");
    affiche(xp.marqueurs, m);
    printf("\nMarqueurs positifs :\n");
    affiche(xp.marqueurs_positifs, p);

    printf("voici les complexités en fonctions de p votre valeur d'entrée m :\n");

        // calcul du nombre maximal d'itération pour la recherche dichotomique
    int iter = 0;
        do{
            iter += 1;
        }while(m >= pow(2, iter)) ;

        printf("%d", iter);
    for (int i = 0; i <= m ; i++){
        printf("%d %d %i %i %i\n", m, i, i * m, iter * i, m);
    }

    // Test strategie 1
    printf("\nStrategie 1\n");
    marqueurs_negatifs = marqueurs_negatifs1(&xp, &cpt);
    printf("Marqueurs negatifs :\n");
    affiche(marqueurs_negatifs, xp.m - xp.p);
    printf("Strategie 1 / nombres OP : %d\n\n", cpt);
    free(marqueurs_negatifs);

    // Test strategie 2
    printf("\nStrategie 2\n");
    marqueurs_negatifs = marqueurs_negatifs2(&xp, &cpt);
    printf("Marqueurs negatifs :\n");
    affiche(marqueurs_negatifs, xp.m - xp.p);
    printf("Strategie 2 / nombres OP : %d\n\n", cpt);
    free(marqueurs_negatifs);

    // Test strategie 3
    printf("\nStrategie 3\n");
    marqueurs_negatifs = marqueurs_negatifs3(&xp, &cpt);
    printf("Marqueurs negatifs :\n");
    affiche(marqueurs_negatifs, xp.m - xp.p);
    printf("Strategie 1 / nombres OP : %d\n\n", cpt);
    free(marqueurs_negatifs);
}

int main(int argc, const char *argv[]) {
    int m, p;

    srand((unsigned int) time(NULL));

    printf("Entrez le nombre de marqueurs positifs : ");
    scanf("%d", &p);
    printf("Entrez le nombre de marqueurs : ");
    scanf("%d", &m);

    test(p, m);

    int tab[10] = {2, 9, 3, 4, 6, 7, 1, 5, 8, 0};
    int tab2[4] = {2, 7, 8, 6};

    mergeSort(tab2, 0, 3);
    affiche(tab2, 4);
    return 0;
}