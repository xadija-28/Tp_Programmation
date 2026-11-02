// Programme principal de l'exercice 2.3 : il appelle les fonctions de volume.c et surface.c
#include <stdio.h>
#include "sphere.h"  // guillemets : fichier du projet ; < > : bibliothèque du système

int main() {
    float rayon = 5.0;
    float volume = calculer_volume(rayon);
    float surface = calculer_surface(rayon);

    printf("Le volume de la sphère de rayon %.2f est %.2f\n", rayon, volume);
    printf("La surface de la sphère de rayon %.2f est %.2f\n", rayon, surface);

    return 0;
}
