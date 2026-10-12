/*
 * Fichier  : boucles.c
 * Objectif : Afficher un triangle rectangle (bords en '*', intérieur en '#')
 *            Version 1 : avec des boucles for
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

    /* Boucle extérieure : une ligne du triangle à chaque tour */
    for (int ligne = 1; ligne <= taille; ligne++)
    {
        /* Boucle intérieure : la ligne n°ligne contient ligne caractères */
        for (int col = 1; col <= ligne; col++)
        {
            /* Bord : 1re colonne, dernière colonne de la ligne, ou dernière ligne */
            if (col == 1 || col == ligne || ligne == taille)
                printf("*");
            else
                printf("#");

            /* Espace entre deux caractères (pas après le dernier) */
            if (col < ligne)
                printf(" ");
        }
        /* Fin de la ligne : une seule fois par tour de la boucle extérieure */
        printf("\n");
    }

    return 0;
}