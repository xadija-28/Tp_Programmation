/*
 * Fichier  : boucles_while.c
 * Objectif : Afficher un triangle rectangle (bords en '*', intérieur en '#')
 *            Version 2 : avec des boucles while
 * Auteurs  : BA Khadidiatou, MBAYE
 */

#include <stdio.h>

int main()
{
    int taille;

    /*
     * PRISE D'INITIATIVE (non demandée par l'énoncé) :
     * tant que la taille n'est pas comprise entre 1 et 9, on redemande la saisie
     */
    do
    {
        printf("Entrez une taille (< 10) : ");
        scanf("%d", &taille);

        if (taille < 1 || taille >= 10)
            printf("Erreur : la taille doit être comprise entre 1 et 9.\n");

    } while (taille < 1 || taille >= 10);
    /* FIN DE LA PRISE D'INITIATIVE */

    int ligne = 1;                      /* départ de la boucle extérieure */
    while (ligne <= taille)             /* condition de la boucle extérieure */
    {
        int col = 1;                    /* remis à 1 à chaque nouvelle ligne */
        while (col <= ligne)            /* condition de la boucle intérieure */
        {
            /* Bord : 1re colonne, dernière colonne de la ligne, ou dernière ligne */
            if (col == 1 || col == ligne || ligne == taille)
                printf("*");
            else
                printf("#");

            /* Espace entre deux caractères (pas après le dernier) */
            if (col < ligne)
                printf(" ");

            col++;                      /* colonne suivante */
        }
        printf("\n");                   /* fin de la ligne */
        ligne++;                        /* ligne suivante */
    }

    return 0;
}
