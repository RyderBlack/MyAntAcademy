# MyAntAcademy

## 🐜 Projet d'Algorithme de Parcours de Graphes

### Description
MyAntAcademy est un projet étudiant qui implémente et compare trois algorithmes classiques de parcours de graphes : l'algorithme BFS (Breadth-First Search), l'algorithme A* (A-Star) et l'algorithme de Dijkstra. Le projet simule le déplacement de fourmis dans différentes configurations de fourmilières, représentées sous forme de grilles.

### 🚀 Fonctionnalités

- Implémentation de l'algorithme BFS pour le parcours en largeur
- Implémentation de l'algorithme A* avec heuristique pour le chemin le plus court
- Implémentation de l'algorithme de Dijkstra pour le chemin de coût minimal
- Système de benchmark pour comparer les performances des trois algorithmes
- Différents niveaux de difficulté de fourmilières (de 4 à 23 pièces)
- Interface en ligne de commande claire et détaillée

### 📊 Résultats du Benchmark

Le projet inclut un système de benchmark qui compare les performances des trois algorithmes sur différentes configurations de fourmilières, affichant :
- Le nombre d'étapes nécessaires pour chaque algorithme
- Le temps d'exécution
- L'algorithme le plus rapide pour chaque configuration
- Une analyse comparative globale

### 🛠️ Installation

1. Cloner le dépôt :
   ```bash
   git clone https://github.com/RyderBlack/MyAntAcademy.git
   cd MyAntAcademy
   ```

2. Créer le dossier pour Dijkstra :
   ```bash
   mkdir -p dijkstra_algo
   ```

3. Compiler le projet avec CMake :
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```

4. Exécuter le benchmark :
   ```bash
   ./bin/MyAntAcademy_benchmark
   ```

5. Ou exécuter un algorithme spécifique :
   ```bash
   ./bin/MyAntAcademy_bfs
   ./bin/MyAntAcademy_astar
   ./bin/MyAntAcademy_dijkstra
   ```

### 📚 Structure du Projet

- `/bfs_algo` : Implémentation de l'algorithme BFS
- `/astar_algo` : Implémentation de l'algorithme A*
- `/dijkstra_algo` : Implémentation de l'algorithme de Dijkstra
- `/benchmark` : Code du benchmark comparatif
- `CMakeLists.txt` : Fichier de configuration CMake

### 👥 Contributeurs

- **Ryhad BOUGHANMI** - [GitHub](https://github.com/RyderBlack/)
- **Arnaud SÉNÉGAS** - [GitHub](https://github.com/senegas-arnaud)
- **Antoine ROUX** - [GitHub](https://github.com/antxinerx)

### 📝 Licence

Ce projet a été réalisé dans le cadre d'un projet étudiant à [La Plateforme](https://laplateforme.io/).

### 📊 Exemple de Sortie du Benchmark

```
ANTHILL                       BFS STEPS    BFS TIME (ms)     A* STEPS    A* TIME (ms)  DIJKSTRA STEPS  DIJKSTRA TIME (ms)      FASTEST
========================================================================================================================================
Small Hill (4 rooms)                6           0.001               6           0.002               6              0.001             BFS
...

==================================================
SUMMARY
--------------------------------------------------
BFS was fastest in:                 2 out of 7 cases
A* was fastest in:                  3 out of 7 cases
Dijkstra was fastest in:            2 out of 7 cases

Total BFS time:                     0.012 ms
Total A* time:                      0.010 ms
Total Dijkstra time:                0.011 ms

Fastest overall:                    A*
```