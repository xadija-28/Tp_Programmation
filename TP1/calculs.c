/*
 * Fichier  : calculs.c
 * Objectif : Effectuer une opération arithmétique ou bit à bit sur deux
 *            entiers num1 et num2, choisie avec un switch selon le caractère op
 * Auteurs  : BA Khadidiatou, MBAYE
 */

#include <stdio.h>

int main()
{
    int num1 = 16;
    int num2 = 3;
    char op = '+';      /* opérateur à appliquer : + - * / % & | ~ */

    switch (op)
    {
        case '+':
            printf("%d + %d = %d\n", num1, num2, num1 + num2);
            break;

        case '-':
            printf("%d - %d = %d\n", num1, num2, num1 - num2);
            break;

        case '*':
            printf("%d * %d = %d\n", num1, num2, num1 * num2);
            break;

        case '/':
            if (num2 == 0)
                printf("Erreur : division par zéro impossible\n");
            else
                printf("%d / %d = %d\n", num1, num2, num1 / num2);
            break;

        case '%':
            if (num2 == 0)
                printf("Erreur : modulo par zéro impossible\n");
            else
                printf("%d %% %d = %d\n", num1, num2, num1 % num2);
            break;

        case '&':
            printf("%d & %d = %d\n", num1, num2, num1 & num2);
            break;

        case '|':
            printf("%d | %d = %d\n", num1, num2, num1 | num2);
            break;

        case '~':
            /* NON bit à bit : un seul opérande, on l'applique à num1 */
            printf("~%d = %d\n", num1, ~num1);
            break;

        default:
            printf("Erreur : opérateur '%c' inconnu\n", op);
            break;
    }

    return 0;
}