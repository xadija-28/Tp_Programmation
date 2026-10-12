/*
 * Fichier  : variables.c
 * Objectif : Déclarer une variable pour chaque type de base du C (signé et
 *            non signé), lui affecter une valeur et l'afficher avec printf()
 * Auteurs  : BA Khadidiatou, MBAYE
 */

#include <stdio.h>
#include <limits.h>   /* valeurs maximales des types entiers (UCHAR_MAX, UINT_MAX...) */

int main()
{
    /* ----- Types caractères ----- */
    char               c   = 'A';
    signed char        sc  = -100;
    unsigned char      uc  = UCHAR_MAX;

    /* ----- Types entiers courts ----- */
    signed short       ss  = -30000;
    unsigned short     us  = USHRT_MAX;

    /* ----- Types entiers ----- */
    signed int         si  = -2000000000;
    unsigned int       ui  = UINT_MAX;

    /* ----- Types entiers longs ----- */
    signed long int    sl  = -9000000000L;
    unsigned long int  ul  = ULONG_MAX;

    /* ----- Types entiers très longs ----- */
    signed long long int   sll = -9000000000000000000LL;
    unsigned long long int ull = ULLONG_MAX;

    /* ----- Types réels (toujours signés) ----- */
    float              f   = -3.14f;
    double             d   = -2.718281828459045;
    long double        ld  = -1.234567890123456789L;

    /* ----- Affichage : chaque type a son propre format dans printf ----- */
    printf("char               : %c\n",   c);
    printf("signed char        : %hhd\n", sc);
    printf("unsigned char      : %hhu\n", uc);
    printf("signed short       : %hd\n",  ss);
    printf("unsigned short     : %hu\n",  us);
    printf("signed int         : %d\n",   si);
    printf("unsigned int       : %u\n",   ui);
    printf("signed long        : %ld\n",  sl);
    printf("unsigned long      : %lu\n",  ul);
    printf("signed long long   : %lld\n", sll);
    printf("unsigned long long : %llu\n", ull);
    printf("float              : %f\n",   f);
    printf("double             : %lf\n",  d);
    printf("long double        : %Lf\n",  ld);

    return 0;
}
