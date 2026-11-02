# TP Programmation – TP2

---

## Exercice 2.1 – Débogage avec GDB

### Compilateur et débogueur : quelle différence ?

| | `gcc -Wall -Wextra` | `gdb` |
|---|---|---|
| Outil | Compilateur avec tous les avertissements activés | Débogueur |
| Quand ? | **Avant** l'exécution | **Pendant** l'exécution |
| Rôle | Analyse le code sans l'exécuter et signale ce qui semble incorrect | Lance le programme, l'arrête à une ligne choisie, affiche les variables et avance ligne par ligne |

### Le bug de `erreurs.c`

```c
int tableau[100];
for (int compteur = 0; compteur < sizeof(tableau); compteur++)
```

`sizeof(tableau)` renvoie une taille en **octets** : 100 entiers × 4 octets = **400**, et non 100.
La boucle écrit donc jusqu'à `tableau[399]`, bien au-delà de la fin du tableau (dernier indice valide : 99).

Le tableau est une variable locale, rangée sur la **pile**. Juste après lui, gcc place un **canari** :
une valeur de contrôle vérifiée à la sortie de `main`. La boucle écrase ce canari, et au `return`
le programme s'arrête avec le message :

```
*** stack smashing detected ***: terminated
```

### Débogage avec GDB

```bash
gcc -ggdb3 erreurs.c -o erreurs   # -ggdb3 ajoute les informations de débogage
gdb erreurs
```

```
(gdb) r                    # lance le programme : il plante (SIGABRT)
(gdb) bt                   # pile d'appels : le plantage est détecté dans main (erreurs.c:11)
(gdb) break erreurs.c:7    # point d'arrêt dans le corps de la boucle
(gdb) r                    # relance : le programme s'arrête à la ligne 7
(gdb) p compteur           # affiche 0
(gdb) p sizeof(tableau)    # affiche 400 -> preuve du bug
(gdb) p tableau[0]@5       # affiche les 5 premières cases du tableau
(gdb) n                    # avance d'une ligne
(gdb) continue             # continue jusqu'au prochain point d'arrêt
(gdb) quit                 # quitte gdb
```

**Remarque :** le point d'arrêt doit être placé **avant** de lancer (ou de relancer) le programme avec `r`.
Si le programme est déjà terminé, gdb répond `No symbol "tableau" in current context`, car les variables n'existent plus.

### Question : compilation avec `gcc -Wall -Wextra erreurs.c`

**Avertissement obtenu :**

```
warning: comparison of integer expressions of different signedness: 'int' and 'long unsigned int' [-Wsign-compare]
```

**Lien avec l'erreur :** l'avertissement porte exactement sur la condition fautive de la boucle.
Il signale que l'on compare `compteur` (un `int`, signé) avec `sizeof(tableau)` (un `size_t`, non signé).
Cela oblige à regarder ce que vaut réellement `sizeof(tableau)` : une taille en octets (400), et non un nombre d'éléments (100).

**Type à donner à `compteur` :** `size_t`, le type renvoyé par `sizeof`.

**Correction de la boucle :**

```c
for (size_t compteur = 0; compteur < sizeof(tableau) / sizeof(tableau[0]); compteur++)
```

`sizeof(tableau) / sizeof(tableau[0])` = 400 / 4 = **100** : le vrai nombre d'éléments du tableau.

---

## Exercice 2.2 – Chaîne de compilation en C

### Les étapes

Quand on tape simplement `gcc aire.c -o aire`, gcc enchaîne en réalité 4 étapes.
On peut les lancer une par une pour observer le résultat de chacune :

| Étape | Commande | Entrée → Sortie | Rôle |
|---|---|---|---|
| 1. Préprocesseur | `gcc -E aire.c -o aire.i` | `.c` → `.i` (code C) | Traite les lignes commençant par `#` : `#include`, `#define`, macros |
| 2. Compilation | `gcc -O2 -S aire.i -o aire.s` | `.i` → `.s` (assembleur) | Traduit le C en instructions assembleur du processeur |
| 3. Assemblage | `gcc -c aire.s -o aire.o` | `.s` → `.o` (fichier objet) | Traduit l'assembleur en code machine binaire |
| 4. Édition de liens | `gcc aire.o -lm -o aire` | `.o` → exécutable | Assemble les fichiers objets et les bibliothèques en un programme complet |
| 5. Exécution | `./aire` | – | Lance le programme |

Résultat de l'exécution :

```
L'aire du cercle de rayon 5.00 est 78.54
```

### Observations sur chaque fichier produit

**`aire.i` (préprocesseur)** – toujours du C, mais :
- il passe de 20 lignes à environ **2 240 lignes** : le contenu de `<stdio.h>` et de `<math.h>` a été copié à la place des `#include` ;
- la macro `M_PI` a disparu, remplacée par sa valeur `3.14159265358979323846` ;
- les commentaires ont été supprimés.

**`aire.s` (compilation)** – du code assembleur x86-64 (instructions `movsd`, `mulsd`, `call printf@PLT`...).
Avec l'option `-O2`, gcc optimise : comme le rayon vaut toujours 5.0, il calcule l'aire **à la compilation**.
`main` n'appelle plus `calculer_aire` : elle passe directement les valeurs constantes à `printf`.

**`aire.o` (assemblage)** – un fichier binaire (`ELF 64-bit relocatable`), illisible avec un éditeur de texte.
Il n'est pas encore exécutable : `nm aire.o` montre que `printf` est marquée `U` (*undefined*).
Le fichier sait qu'il a besoin de `printf`, mais ne sait pas encore où elle se trouve.

**`aire` (édition de liens)** – l'exécutable final (`ELF 64-bit pie executable`).
L'éditeur de liens a relié l'appel à `printf` à la bibliothèque C standard (`libc`).

### Rôle de l'option `-lm`

`-lm` demande de lier la bibliothèque mathématique `libm` (fonctions `sqrt`, `pow`, `cos`...).
Elle est nécessaire dès que le programme **appelle** une de ces fonctions.
Ici, `aire.c` utilise seulement `M_PI`, qui est une macro remplacée par le préprocesseur :
aucune fonction de `libm` n'est appelée, donc le programme fonctionnerait aussi sans `-lm`.

### Fichiers utilisés

| Fichier | Description |
|---|---|
| `TP2/aire.c` | Code source |
| `TP2/aire.i` | Résultat du préprocesseur |
| `TP2/aire.s` | Code assembleur |
| `TP2/aire.o` | Fichier objet |
| `TP2/aire` | Exécutable final |

---

## Exercice 2.3 – Compilation d'un programme multi-fichiers

### Organisation du programme `sphere`

| Fichier | Contenu |
|---|---|
| `sphere.h` | Prototypes de `calculer_volume` et `calculer_surface` (protégés par `#ifndef SPHERE_H`) |
| `volume.c` | Définition de `calculer_volume` |
| `surface.c` | Définition de `calculer_surface` |
| `main.c` | Programme principal, qui appelle les deux fonctions |

`main.c`, `volume.c` et `surface.c` incluent tous `sphere.h` : c'est grâce à ce fichier que `main.c`
connaît les fonctions sans avoir leur code.

### Compilation étape par étape

```bash
# Préprocesseur : un .i par fichier .c
gcc -E main.c -o main.i
gcc -E volume.c -o volume.i
gcc -E surface.c -o surface.i

# Compilation + assemblage (-c) avec optimisation -O3 : un .o par fichier
gcc -O3 -c main.i -o main.o
gcc -O3 -c volume.i -o volume.o
gcc -O3 -c surface.i -o surface.o

# Édition de liens : les 3 fichiers objets sont réunis en un seul exécutable
gcc main.o volume.o surface.o -lm -o sphere

# Exécution
./sphere
```

Résultat :

```
Le volume de la sphère de rayon 5.00 est 523.60
La surface de la sphère de rayon 5.00 est 314.16
```

**Remarque :** chaque fichier `.c` est compilé **séparément**. Le contenu de `sphere.h` est donc
recopié dans chaque `.i` par le préprocesseur.

### Ce que contient chaque fichier objet (`nm`)

| Fichier | Définit (`T`) | A besoin de (`U`, non défini) |
|---|---|---|
| `main.o` | `main` | `calculer_volume`, `calculer_surface`, `printf` |
| `volume.o` | `calculer_volume` | `pow` |
| `surface.o` | `calculer_surface` | – |

Chaque `.o` contient des « trous » (les symboles `U`). C'est l'**édition de liens** qui les comble :
- `calculer_volume` et `calculer_surface` sont trouvées dans `volume.o` et `surface.o` ;
- `printf` est trouvée dans la bibliothèque C standard (`libc`) ;
- `pow` est trouvée dans la bibliothèque mathématique, d'où l'option **`-lm`**.

Si un élément manque, l'édition de liens échoue :

```
# sans -lm
volume.c:(.text+0x15): undefined reference to `pow'

# sans volume.o
main.c:(.text.startup+0x14): undefined reference to `calculer_volume'
```

`surface.o` n'a pas besoin de `pow` : avec `-O3`, gcc a remplacé `pow(rayon, 2)` par `rayon * rayon`.

### Modification de `volume.c` seulement

Exemple : on remplace `pow(rayon, 3)` par `rayon * rayon * rayon` dans `volume.c`.

**Seules les étapes concernant `volume.c` doivent être refaites, puis l'édition de liens :**

```bash
gcc -E volume.c -o volume.i
gcc -O3 -c volume.i -o volume.o
gcc main.o volume.o surface.o -lm -o sphere
```

| Fichier | À refaire ? | Pourquoi |
|---|---|---|
| `volume.i`, `volume.o` | **Oui** | Son code source a changé |
| `main.o`, `surface.o` | Non | Leurs sources n'ont pas changé : leurs `.o` restent identiques (vérifié avec `md5sum`) |
| `sphere` | **Oui** | L'exécutable doit être refait avec le nouveau `volume.o` |

**Intérêt de la compilation séparée :** dans un gros projet, modifier un fichier oblige à recompiler
uniquement ce fichier, puis à refaire l'édition de liens, et non à recompiler tout le projet.
C'est ce que l'outil `make` automatise.

**Attention :** si l'on modifie `sphere.h`, il faut recompiler **tous** les fichiers `.c` qui l'incluent
(`main.c`, `volume.c` et `surface.c`).

---

## Programme `chaine.c` – Chaînes de caractères

Le programme lit deux chaînes, puis affiche leur longueur, une copie et leur concaténation.

| Fonction | Rôle | Pourquoi ce choix |
|---|---|---|
| `fgets` | Lit une ligne | Accepte les espaces et respecte la taille du tableau, contrairement à `scanf("%s")` |
| `strcspn` | Trouve la position du `\n` | Permet d'enlever le retour à la ligne gardé par `fgets` |
| `strlen` | Calcule la longueur | Le `\0` final n'est pas compté |
| `strcpy` | Copie une chaîne | Un tableau ne peut pas être affecté avec `=` |
| `strcat` | Ajoute une chaîne à la suite | `concat` fait 200 caractères pour pouvoir contenir les deux chaînes |

Résultat avec `bonjour` et `monde` :

```
Longueur de "bonjour" : 7
Longueur de "monde" : 5

Copie de la première chaîne : "bonjour"

Concaténation : "bonjourmonde"
```

---

## Programme `bd_ecole.c` – Structure d'étudiant.e.s

Le programme gère 5 étudiant.e.s dans un tableau de `struct etudiant`, en trois temps :

1. **Initialisation** avec `strcpy` : chaque champ reçoit une valeur par défaut (`Inconnu`, `0.0`) ;
2. **Saisie** avec `fgets`, pour accepter les espaces dans une adresse ;
3. **Affichage** sous forme de tableau, avec la fonction `afficher_etudiant`.

Les notes sont lues avec `fgets` puis `sscanf`. Avec `scanf` seul, le `\n` resterait en attente et serait lu
par le `fgets` suivant, qui recevrait alors une ligne vide.

**Limites :**
- une note qui n'est pas un nombre garde sa valeur initiale `0.00` ;
- si un nom dépasse la taille prévue (29 caractères), la fin est lue par la saisie suivante.

---

## Programme `phrases.c` – Recherche dans un fichier

Le programme demande un nom de fichier et une phrase, puis compte les occurrences de la phrase dans chaque ligne.

- `fopen` ouvre le fichier. Son résultat est testé, car il vaut `NULL` si le fichier n'existe pas.
- `fgets` lit le fichier ligne par ligne, ce qui permet d'afficher le numéro de chaque ligne.
- `strstr` donne la position de la phrase. On reprend ensuite la recherche juste après cette position.
- Une phrase vide est refusée : elle serait trouvée partout et le comptage ne s'arrêterait pas.

Résultat avec `TP2/test.txt` et la phrase `chat` :

```
Ligne   1 : 1 occurrence(s)  |  Le chat dort.
Ligne   2 : 2 occurrence(s)  |  Le chien et le chat jouent avec un autre chat.
Ligne   4 : 3 occurrence(s)  |  chat chat chat

Total : 6 occurrence(s) dans 4 ligne(s) lue(s).
```

**Limite :** les occurrences qui se chevauchent ne comptent qu'une fois (`aa` dans `aaa` : 1 occurrence).

---

## Programme `couleurs.c` – Couleurs distinctes

Le programme stocke 100 couleurs dans un tableau de structures `Couleur`, puis affiche chaque couleur
distincte avec son nombre d'occurrences.

**Saisie :** chaque couleur s'écrit avec quatre entiers (rouge, vert, bleu, alpha), par exemple `255 0 0 255`.
Une lettre comme `R` provoque le message `Erreur de saisie.`

**Méthode :** pour chaque case `i`, on regarde si la même couleur existe avant `i`.
- Si oui, elle a déjà été traitée : on passe à la suivante ;
- Si non, on compte ses occurrences dans tout le tableau, puis on l'affiche.

La fonction `sontIdentiques` évite de répéter la comparaison des quatre composantes.

Pour tester sans taper 100 lignes :

```bash
for i in $(seq 1 100); do echo "$((i%3*100)) 50 25 255"; done | ./couleurs
```

Résultat :

```
Couleurs distinctes et occurrences :
R=100, G=50, B=25, A=255 : 34 occurrence(s)
R=200, G=50, B=25, A=255 : 33 occurrence(s)
R=0, G=50, B=25, A=255 : 33 occurrence(s)
```

---

## Exercice 2.8 – Rechercher une phrase dans un tableau (`chercher.c`)

Le programme contient 10 phrases dans un tableau de tableaux de caractères et indique si la phrase saisie s'y trouve.

La recherche n'utilise aucune fonction de bibliothèque. `stdio.h` sert seulement à la saisie et à l'affichage :

| Fonction écrite | Remplace | Rôle |
|---|---|---|
| `enlever_retour_ligne` | `strcspn` | Enlève le `\n` gardé par `fgets` |
| `phrases_identiques` | `strcmp` | Compare deux phrases caractère par caractère |

**Méthode :** on compare la saisie à chaque phrase et on s'arrête à la première égalité.
La comparaison exige que les deux phrases finissent au même endroit : `Il fait` n'est donc pas trouvée,
car ce n'est que le début d'une phrase du tableau. La recherche respecte aussi les majuscules.

Résultats :

```
La programmation en C est amusante.  ->  Phrase trouvée
Je préfère le Python.                ->  Phrase non trouvée
```

---

## Interpréteur (`interpreteur/repl.c`)

Pour l'instant, seul `repl.c` contient du code. C'est une boucle qui lit une commande et la traite :

| Commande | Effet |
|---|---|
| `echo <texte>` | Affiche `Echo: <texte>` |
| `quit` | Arrête le programme, comme Ctrl-D |
| Autre | Affiche un message d'aide |

Les autres fichiers du dossier sont vides.
