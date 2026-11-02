/*
 * Fichier  : chaine.c
 * Objectif : Demander deux chaînes à l'utilisateur, puis calculer leur
 *            longueur, copier une chaîne dans une autre et les concaténer
 * Auteurs  : BA Khadidiatou, MBAYE
 */
#include <stdio.h>
#include <string.h>   /* strlen, strcpy, strcat, strcspn */
int main()
{
    char chaine1[100];
    char chaine2[100]; 
    char copie[100];
    char concat[200];   /* assez grand pour contenir les deux chaînes */

    /* ----- Saisie des deux chaînes ----- */
    /* fgets accepte les espaces et ne dépasse pas la taille du tableau */
    printf("Entrez la première chaîne : ");
    fgets(chaine1, sizeof(chaine1), stdin);
    chaine1[strcspn(chaine1, "\n")] = '\0'; /* on enlève le retour à la ligne gardé par fgets */

    printf("Entrez la deuxième chaîne : ");
    fgets(chaine2, sizeof(chaine2), stdin);
    chaine2[strcspn(chaine2, "\n")] = '\0';

    /* ----- 1. Longueur ----- */
    printf("\nLongueur de \"%s\" : %zu\n", chaine1, strlen(chaine1));
    printf("Longueur de \"%s\" : %zu\n", chaine2, strlen(chaine2));

    /* ----- 2. Copie de chaine1 dans copie ----- */
    /* copie = chaine1 serait refusé : un tableau ne s'affecte pas, on utilise strcpy */
    strcpy(copie, chaine1);
    printf("\nCopie de la première chaîne : \"%s\"\n", copie);

    /* ----- 3. Concaténation de chaine1 et chaine2 ----- */
    strcpy(concat, chaine1);   /* on commence par chaine1 */
    strcat(concat, chaine2);   /* puis on ajoute chaine2 à la suite (strcat a besoin d'une chaîne déjà terminée) */
    printf("\nConcaténation : \"%s\"\n", concat);

    return 0;
}