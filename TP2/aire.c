// Directive de préprocesseur pour inclure la bibliothèque mathématique
#include <math.h>  // Pour utiliser la constante M_PI

#include <stdio.h> 

// Fonction pour calculer l'aire d'un cercle
float calculer_aire(float rayon) {  // une fonction sépare le calcul de l'affichage
    // Utilisation de la constante pi de la bibliothèque mathématique
    return M_PI * rayon * rayon;
}

// Point d'entrée du programme
int main() {
    float rayon = 5.0; // valeur fixe : gcc -O2 calcule l'aire dès la compilation (voir README)
    float aire = calculer_aire(rayon);
    // Affichage du résultat
    printf("L'aire du cercle de rayon %.2f est %.2f\n", rayon, aire);
    return 0;
}

