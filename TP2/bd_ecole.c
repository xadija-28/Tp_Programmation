/*
 * Fichier  : bd_ecole.c
 * Objectif : Gérer les données de 5 étudiant.e.s à l'aide d'une structure :
 *            initialisation avec strcpy, saisie par l'utilisateur, puis affichage
 * Auteurs  : BA Khadidiatou, MBAYE
 */

#include <stdio.h>
#include <string.h>

/* Les tailles sont dans des #define : pour en changer une, on ne modifie qu'une seule ligne */
#define NB_ETUDIANTS 5
#define NB_NOTES     2
#define TAILLE_NOM   30
#define TAILLE_ADR   100

/* Structure représentant un étudiant : elle regroupe ses informations en une seule donnée */
struct etudiant
{
    char nom[TAILLE_NOM];
    char prenom[TAILLE_NOM];
    char adresse[TAILLE_ADR];
    float notes[NB_NOTES];      /* notes[0] : programmation, notes[1] : système */
};

/* Lit une ligne au clavier (espaces compris) et retire le '\n' final.
   fgets remplace scanf("%s"), qui s'arrêterait au premier espace (ex. "12 rue Hugo")
   et ne limiterait pas le nombre de caractères écrits dans le tableau.
   Limite : si la saisie est trop longue, la fin est lue par la saisie suivante. */
void lire_ligne(char *chaine, int taille)
{
    if (fgets(chaine, taille, stdin) == NULL)
        chaine[0] = '\0';
    else
        chaine[strcspn(chaine, "\n")] = '\0';
}

/* Affiche toutes les informations d'un étudiant */
void afficher_etudiant(struct etudiant e)
{
    printf("%-12s %-12s %-30s %6.2f %6.2f\n",
           e.nom, e.prenom, e.adresse, e.notes[0], e.notes[1]);
}

int main()
{
    struct etudiant etudiants[NB_ETUDIANTS];
    char saisie[TAILLE_ADR];
    int i, j;

    /* ===== Initialisation des données avec strcpy ===== */
    /* En C, on ne peut pas écrire tableau = "texte" : il faut copier avec strcpy */
    for (i = 0; i < NB_ETUDIANTS; i++)
    {
        strcpy(etudiants[i].nom, "Inconnu");
        strcpy(etudiants[i].prenom, "Inconnu");
        strcpy(etudiants[i].adresse, "Non renseignée");
        for (j = 0; j < NB_NOTES; j++)
            etudiants[i].notes[j] = 0.0;
    }

    /* ===== Saisie des informations de chaque étudiant ===== */
    for (i = 0; i < NB_ETUDIANTS; i++)
    {
        printf("\n--- Étudiant %d ---\n", i + 1);

        /* On lit dans un tableau temporaire, puis on copie avec strcpy */
        printf("Nom : ");
        lire_ligne(saisie, TAILLE_NOM);
        strcpy(etudiants[i].nom, saisie);

        printf("Prénom : ");
        lire_ligne(saisie, TAILLE_NOM);
        strcpy(etudiants[i].prenom, saisie);

        printf("Adresse : ");
        lire_ligne(saisie, TAILLE_ADR);
        strcpy(etudiants[i].adresse, saisie);

        /* On lit toute la ligne puis sscanf en extrait le nombre : avec scanf seul, le '\n'
           resterait en attente et perturberait le prochain fgets.
           Si la note n'est pas un nombre, elle garde sa valeur initiale 0.0 */
        printf("Note de programmation : ");
        lire_ligne(saisie, TAILLE_ADR);
        sscanf(saisie, "%f", &etudiants[i].notes[0]);

        printf("Note de système : ");
        lire_ligne(saisie, TAILLE_ADR);
        sscanf(saisie, "%f", &etudiants[i].notes[1]);
    }

    /* ===== Affichage des informations ===== */
    printf("\n%-12s %-12s %-30s %6s %6s\n",
           "Nom", "Prénom", "Adresse", "Prog", "Sys");
    for (i = 0; i < NB_ETUDIANTS; i++)
        afficher_etudiant(etudiants[i]);

    return 0;
}
