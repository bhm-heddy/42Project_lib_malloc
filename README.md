# 42Project_lib_malloc

_One Heap to malloc them all, One Heap to free them, One Heap to coalesce, and in the memory bind them..._


------


_Ce projet consiste à écrire une librairie de gestion de l’allocation dynamique de lamémoire. Afin de pouvoir la faire utiliser par des programmes déjà existant sans les modifier ni les recompiler, vous devrez réécrire les fonctions malloc(3), free(3), calloc(3) et realloc(3) de la libc._ 

[Sujet](https://github.com/bhm-heddy/42project_malloc/blob/master/ft_malloc.fr.pdf)

------



## How to Run
  - clone this repository `https://github.com/bhm-heddy/42project_malloc`
  - Compil `make`
  - Run `./run_test.sh [commande]`

Ou exporter directement les variables de _run_test.sh_ dans votre environnement. 


## Features
  - Défragmentation en continue de la mémoire par merge des _chunks_ libérés par l'utilisateur.
  - Gestion du multi-threading avec la lib pthread 
  - Variables d'environnement de debug et d'information : `M_DEBUG=[1-4] M_PATH=[File_path] ./run_test.sh [commande]`.

* M_DEBUG de niveau:

  **1** Affiche les appels aux fonctions de lib_malloc, avec la mémoire demandée et l'addresse retourner.
  
  **2** Niveau 1 + information des _headers_ des zones pré-alouées : _chunks_ totales, _chunks_ utilisés, début - fin. 
  
  **3** Niveau 2 + affichage des informations pour chaque _chunks_ utilisés. 
  
  **4** Niveau 3 + affichage de tous les _chunks_ libre ou utilisés.
  
 * M_PATH

  Si vide, les informations seront écrites dans la sortie d'erreur.
  Si non, il faut donner un **PATH absolu**



