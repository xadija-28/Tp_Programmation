/*
 * Fichier  : chercher.c
 * Objectif : Rechercher si une phrase donnée est présente dans un tableau
 *            de 10 phrases, sans fonction de bibliothèque pour la recherche
 * Auteurs  : BA Khadidiatou, MBAYE
 */

#include <stdio.h>    /* uniquement pour la saisie (fgets) et l'affichage (printf) */

#define NB_PHRASES    10
#define TAILLE_PHRASE 100

/* Enlève le retour à la ligne gardé par fgets : sans cela, la saisie
   ne serait jamais égale à une phrase du tableau */
void enlever_retour_ligne(char texte[])
{
    int i = 0;

    while (texte[i] != '\0')
    {
        if (texte[i] == '\n')
        {
            texte[i] = '\0';
            return;
        }
        i++;
    }
}

/* Compare deux phrases caractère par caractère, à la place de strcmp.
   Renvoie 1 si elles sont identiques, et 0 sinon */
int phrases_identiques(char phrase1[], char phrase2[])
{
    int i = 0;

    /* On avance tant que les caractères sont égaux et que la phrase n'est pas finie */
    while (phrase1[i] != '\0' && phrase1[i] == phrase2[i])
        i++;

    /* Égales seulement si on est au '\0' des deux phrases : ce test évite qu'un
       simple début de phrase, comme "Il fait", soit considéré comme trouvé */
    return phrase1[i] == phrase2[i];
}

int main()
{
    /* Tableau de tableaux de caractères : 10 phrases de 99 caractères maximum,
       plus le '\0' final. Un caractère accentué occupe 2 cases */
    char phrases[NB_PHRASES][TAILLE_PHRASE] = {
        "Bonjour, comment ça va ?",
        "Le temps est magnifique aujourd'hui.",
        "C'est une belle journée.",
        "La programmation en C est amusante.",
        "Les tableaux en C sont puissants.",
        "Les pointeurs en C peuvent être déroutants.",
        "Il fait beau dehors.",
        "La recherche dans un tableau est intéressante.",
        "Les structures de données sont importantes.",
        "Programmer en C, c'est génial."
    };
    char recherche[TAILLE_PHRASE];
    int trouvee = 0;    /* passe à 1 dès que la phrase est trouvée */

    /* fgets est choisi car une phrase contient des espaces */
    printf("Phrase à rechercher : ");
    if (fgets(recherche, sizeof(recherche), stdin) == NULL)
    {
        printf("Erreur de saisie.\n");
        return 1;
    }
    enlever_retour_ligne(recherche);

    /* On compare la saisie à chaque phrase. Inutile de continuer après
       l'avoir trouvée : la condition !trouvee arrête alors la boucle */
    for (int i = 0; i < NB_PHRASES && !trouvee; i++)
    {
        if (phrases_identiques(recherche, phrases[i]))
            trouvee = 1;
    }

    if (trouvee)
        printf("Phrase trouvée\n");
    else
        printf("Phrase non trouvée\n");

    return 0;
}
