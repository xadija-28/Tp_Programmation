#include <math.h>
#include "sphere.h"  // permet au compilateur de vérifier que le code suit le prototype

// Fonction pour calculer la surface d'une sphère : 4 * pi * r^2
float calculer_surface(float rayon) {
    return 4 * M_PI * pow(rayon, 2);
}
