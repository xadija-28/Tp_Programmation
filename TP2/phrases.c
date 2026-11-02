/*
 * Fichier  : phrases.c
 * Objectif : Rechercher une phrase dans un fichier texte et compter,
 *            pour chaque ligne, le nombre d'occurrences de cette phrase
 * Auteurs  : BA Khadidiatou, MBAYE
 */

#include <stdio.h>
#include <string.h>   /* strlen, strstr, strcspn */

/* Lit une ligne au clavier et enlève le retour à la ligne final.
   fgets est choisi car une phrase ou un nom de fichier peut contenir des espaces */
void lire_texte(char texte[], int taille)
{
    fgets(texte, taille, stdin);
    texte[strcspn(texte, "\n")] = '\0';
}

/* Compte le nombre de fois où phrase apparaît dans ligne.
   Fonction séparée pour que la boucle du main reste simple à lire */
int compter_occurrences(char ligne[], char phrase[])
{
    int compteur = 0;
    char *position = strstr(ligne, phrase);   /* première occurrence */

    while (position != NULL) {
        compteur++;
        /* on cherche la suivante juste après celle qu'on vient de trouver : sans ce
           décalage, strstr retrouverait la même et la boucle ne s'arrêterait jamais.
           Les occurrences qui se chevauchent ne comptent qu'une fois ("aa" dans "aaa" : 1) */
        position = strstr(position + strlen(phrase), phrase);
    }
    return compteur;
}

int main()
{
    char nom_fichier[100];
    char phrase[100];
    char ligne[1024];
    int numero_ligne = 0;
    int total = 0;

    /* ----- 1. Saisie du nom du fichier et de la phrase ----- */
    printf("Nom du fichier : ");
    lire_texte(nom_fichier, sizeof(nom_fichier));

    printf("Phrase à rechercher : ");
    lire_texte(phrase, sizeof(phrase));

    /* Une phrase vide serait trouvée partout, et la boucle de comptage ne s'arrêterait pas */
    if (strlen(phrase) == 0) {
        printf("Erreur : la phrase à rechercher est vide.\n");
        return 1;
    }

    /* ----- 2. Ouverture du fichier en lecture ----- */
    /* fopen renvoie NULL en cas d'échec (fichier absent, par exemple) : il faut le tester */
    FILE *fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier \"%s\".\n", nom_fichier);
        return 1;
    }

    /* ----- 3. Lecture ligne par ligne et comptage ----- */
    /* Limite : une ligne de plus de 1023 caractères est lue en plusieurs morceaux */
    printf("\nRecherche de \"%s\" dans \"%s\" :\n\n", phrase, nom_fichier);

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        numero_ligne++;
        ligne[strcspn(ligne, "\n")] = '\0';

        int nb = compter_occurrences(ligne, phrase);
        if (nb > 0) {
            printf("Ligne %3d : %d occurrence(s)  |  %s\n", numero_ligne, nb, ligne);
            total += nb;
        }
    }

    fclose(fichier);

    /* ----- 4. Résultat global ----- */
    printf("\nTotal : %d occurrence(s) dans %d ligne(s) lue(s).\n", total, numero_ligne);

    return 0;
}