/*
 * Fichier  : couleurs.c
 * Objectif : Stocker 100 couleurs (R, G, B, A) et afficher les couleurs
 *            distinctes avec leur nombre d'occurrences
 * Auteurs  : BA Khadidiatou, MBAYE
 */

#include <stdio.h>

// #define évite d'écrire 100 partout : pour tester avec moins de couleurs,
// il suffit de changer cette ligne.
#define NB_COULEURS 100

// Structure choisie pour regrouper les quatre composantes d'une couleur.
// On peut ainsi manipuler une couleur comme une seule donnée.
typedef struct {
    int r;
    int g;
    int b;
    int a;
} Couleur;

// Fonction choisie pour éviter de répéter la comparaison des quatre composantes.
// Elle renvoie 1 si les couleurs sont identiques, et 0 sinon.
int sontIdentiques(Couleur c1, Couleur c2) {
    return c1.r == c2.r && c1.g == c2.g
        && c1.b == c2.b && c1.a == c2.a;
}

int main(void) {
    // Le tableau stocke les 100 couleurs sous forme de structures Couleur.
    Couleur couleurs[NB_COULEURS];

    // scanf est utilisé pour lire les quatre composantes de chaque couleur.
    // Il attend quatre nombres entiers, par exemple : 255 0 0 255
    for (int i = 0; i < NB_COULEURS; i++) {
        printf("Couleur %d (R G B A) : ", i + 1);

        if (scanf("%d %d %d %d",
                  &couleurs[i].r, &couleurs[i].g,
                  &couleurs[i].b, &couleurs[i].a) != 4) { // scanf renvoie le nombre de valeurs lues
            printf("Erreur de saisie.\n");
            return 1;
        }
    }

    printf("\nCouleurs distinctes et occurrences :\n");

    for (int i = 0; i < NB_COULEURS; i++) {
        int dejaAffichee = 0;

        // On vérifie si cette couleur a déjà été rencontrée.
        // Seules les cases avant i sont regardées : ainsi, chaque couleur
        // n'est affichée qu'une fois, à sa première apparition.
        for (int j = 0; j < i; j++) {
            // On appelle la fonction pour comparer les quatre composantes.
            if (sontIdentiques(couleurs[i], couleurs[j])) {
                dejaAffichee = 1;
                break;
            }
        }

        // Si elle a déjà été affichée, on passe à la couleur suivante.
        if (dejaAffichee) {
            continue;
        }

        // On compte le nombre d'occurrences de cette couleur.
        // Ici on parcourt tout le tableau, en comptant la couleur elle-même.
        int occurrences = 0;
        for (int j = 0; j < NB_COULEURS; j++) {
            if (sontIdentiques(couleurs[i], couleurs[j])) {
                occurrences++;
            }
        }

        printf("R=%d, G=%d, B=%d, A=%d : %d occurrence(s)\n",
               couleurs[i].r, couleurs[i].g,
               couleurs[i].b, couleurs[i].a,
               occurrences);
    }

    return 0;
}