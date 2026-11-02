/*
 * Fichier  : sizeof_types.c
 * Objectif : Afficher la taille en octets de chaque type de base du C
 * Auteurs  : BA Khadidiatou, MBAYE
 */

#include <stdio.h>

int main()
{
    /* sizeof renvoie une valeur de type size_t : le format adapté est %zu.
       Les tailles dépendent de la machine : c'est pour cela qu'on les affiche. */

    printf("char               : %zu octet(s)\n", sizeof(char));
    printf("signed char        : %zu octet(s)\n", sizeof(signed char));
    printf("unsigned char      : %zu octet(s)\n", sizeof(unsigned char));

    printf("short              : %zu octet(s)\n", sizeof(short));
    printf("unsigned short     : %zu octet(s)\n", sizeof(unsigned short));

    printf("int                : %zu octet(s)\n", sizeof(int));
    printf("unsigned int       : %zu octet(s)\n", sizeof(unsigned int));

    printf("long int           : %zu octet(s)\n", sizeof(long int));
    printf("unsigned long int  : %zu octet(s)\n", sizeof(unsigned long int));

    printf("long long int      : %zu octet(s)\n", sizeof(long long int));

    printf("float              : %zu octet(s)\n", sizeof(float));
    printf("double             : %zu octet(s)\n", sizeof(double));
    printf("long double        : %zu octet(s)\n", sizeof(long double));

    return 0;
}