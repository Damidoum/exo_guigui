cmake_minimum_required(VERSION 3.10)
project(Labyrinthe C)

# Ajoute les options de compilation
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall")

# Fichier source principal
set(SOURCE main_sans_bifurcation.c)

# Bibliothèque externe (chemin de la bibliothèque)
link_directories(${CMAKE_SOURCE_DIR}) # Recherche dans le répertoire courant

# Génération de l'exécutable
add_executable(main ${SOURCE})

# Lien avec la bibliothèque
target_link_libraries(main simulation_labyrinthe_linux)
