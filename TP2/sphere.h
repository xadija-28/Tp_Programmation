// #ifndef évite que ce fichier soit pris en compte deux fois dans une même compilation
#ifndef SPHERE_H
#define SPHERE_H

// Ce fichier contient seulement les prototypes : main.c connaît ainsi les fonctions
// sans avoir leur code, qui se trouve dans volume.c et surface.c.

// Fonction pour calculer le volume d'une sphère
float calculer_volume(float rayon);

// Fonction pour calculer la surface d'une sphère
float calculer_surface(float rayon);

#endif
