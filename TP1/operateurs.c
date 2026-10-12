/*
 * Fichier  : operateurs.c
 * Objectif : Utiliser les opérateurs arithmétiques et de comparaison
 *            sur deux variables a = 16 et b = 3
 * Auteurs  : BA Khadidiatou, MBAYE
 */

#include <stdio.h>

int main()
{
    int a = 16;
    int b = 3;

    /* ----- Opérateurs arithmétiques ----- */
    printf("a + b  = %d\n", a + b);    /* addition */
    printf("a - b  = %d\n", a - b);    /* soustraction */
    printf("a * b  = %d\n", a * b);    /* multiplication */
    printf("a / b  = %d\n", a / b);    /* division entière : 16 / 3 = 5 */
    printf("a %% b  = %d\n", a % b);   /* modulo : reste de la division, 16 % 3 = 1 */

    /* ----- Opérateurs de comparaison : le résultat vaut 1 (vrai) ou 0 (faux) ----- */
    printf("a == b = %d\n", a == b);   /* égalité */
    printf("a > b  = %d\n", a > b);    /* supérieur */

    return 0;
}