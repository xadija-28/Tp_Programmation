#include <stdio.h>

int main() { // le bug est laissé volontairement pour l'exercice 2.1 (voir README)
   int tableau[100]; // 100 cases, numérotées de 0 à 99

   for (int compteur = 0; compteur < sizeof(tableau); compteur++) { // Erreur : sizeof donne 400 octets, pas 100 cases
       tableau[compteur] = tableau[compteur] * 2; // écrit hors du tableau dès compteur = 100
   }
   
   return 0;
}
