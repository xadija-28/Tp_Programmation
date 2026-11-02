#include <math.h>
#include "sphere.h"  // permet au compilateur de vérifier que le code suit le prototype

// Fonction pour calculer le volume d'une sphère : 4/3 * pi * r^3
// On écrit 4.0 / 3.0 car 4 / 3 entre entiers vaudrait 1 (division entière).
float calculer_volume(float rayon) {
    return (4.0 / 3.0) * M_PI * pow(rayon, 3);
}
