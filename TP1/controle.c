/*
 * Fichier  : controle.c
 * Objectif : Parcourir les nombres de 1 à 1000 et afficher ceux qui
 *            respectent trois conditions, avec les boucles for, while,
 *            do..while et les instructions if, else, break, continue
 * Auteurs  : BA Khadidiatou, MBAYE
 */

#include <stdio.h>

int main()
{
    int n;

    /* ===== Condition 1 : divisible par 4 mais pas par 6 (boucle for) ===== */
    printf("Divisibles par 4 mais pas par 6 :\n");

    for (n = 1; n <= 1000; n++)
    {
        /* Si le nombre ne convient pas, continue passe directement au suivant */
        if (n % 4 != 0 || n % 6 == 0)
            continue;

        printf("%d ", n);
    }
    printf("\n\n");

    /* ===== Condition 2 : pair et divisible par 8 (boucle while) ===== */
    printf("Pairs et divisibles par 8 :\n");

    n = 1;
    while (1)                           /* boucle sans fin, arrêtée par break */
    {
        if (n > 1000)
            break;                      /* on sort de la boucle après 1000 */
        else if (n % 2 == 0 && n % 8 == 0)
            printf("%d ", n);

        n++;
    }
    printf("\n\n");

    /* ===== Condition 3 : divisible par 5 ou 7 mais pas par 10 (boucle do..while) ===== */
    printf("Divisibles par 5 ou 7 mais pas par 10 :\n");

    n = 1;
    do
    {
        if ((n % 5 == 0 || n % 7 == 0) && n % 10 != 0)
            printf("%d ", n);

        n++;
    } while (n <= 1000);
    printf("\n");

    return 0;
}