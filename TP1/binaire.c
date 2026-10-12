/*
 * Fichier  : binaire.c
 * Objectif : Convertir un entier en binaire avec des divisions par 2
 *            et afficher ses bits dans le bon ordre
 * Auteurs  : BA Khadidiatou, MBAYE
 */

#include <stdio.h>

int main()
{
    int nombre = 4096;      /* valeur à convertir (tester aussi 0, 65536, 65535, 1024) */

    int bits[32];           /* tableau pour ranger les restes (32 bits maximum pour un int) */
    int nb_bits = 0;        /* nombre de bits obtenus */
    int n = nombre;         /* copie de nombre, qu'on va diviser */

    /* Cas particulier : 0 s'écrit 0 en binaire (la boucle ne tournerait pas) */
    if (n == 0)
    {
        bits[0] = 0;
        nb_bits = 1;
    }

    /* Divisions successives par 2 : chaque reste est un bit,
       du bit de poids faible (à droite) vers le bit de poids fort (à gauche) */
    while (n > 0)
    {
        bits[nb_bits] = n % 2;   /* reste de la division : 0 ou 1 */
        n = n / 2;               /* on continue avec le quotient */
        nb_bits++;
    }

    /* Les bits ont été obtenus à l'envers : on les affiche du dernier au premier */
    printf("%d en binaire : ", nombre);
    for (int i = nb_bits - 1; i >= 0; i--)
        printf("%d", bits[i]);
    printf("\n");

    return 0;
}