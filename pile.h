#ifndef PILE_H
#define PILE_H

#include "modelisation_robot_labyrinthe.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* ---- Pile de Directions ---- */

typedef struct Noeud_Direction
{
    Direction valeur;
    struct Noeud_Direction *suivant;
} Noeud_Direction;

typedef struct
{
    Noeud_Direction *sommet;
} Pile_Directions;

/* Initialiser une pile de directions */
void initialiserPileDirections(Pile_Directions *pile)
{
    pile->sommet = NULL;
}

/* Vérifier si une pile de directions est vide */
bool estVidePileDirections(const Pile_Directions *pile)
{
    return pile->sommet == NULL;
}

/* Empiler une direction dans la pile */
void empilerDirection(Pile_Directions *pile, Direction valeur)
{
    Noeud_Direction *nouveau = (Noeud_Direction *)malloc(sizeof(Noeud_Direction));
    if (nouveau == NULL)
    {
        printf("Erreur d'allocation mémoire\n");
        return;
    }
    nouveau->valeur = valeur;
    nouveau->suivant = pile->sommet;
    pile->sommet = nouveau;
}

/* Extraire une direction de la pile */
Direction depilerDirection(Pile_Directions *pile)
{
    if (estVidePileDirections(pile))
    {
        printf("La pile de directions est vide\n");
        return -1;
    }
    Noeud_Direction *temp = pile->sommet;
    Direction resultat = temp->valeur;
    pile->sommet = temp->suivant;
    free(temp);
    return resultat;
}
Pile_Directions *copierPileDirections(const Pile_Directions *source)
{
    Pile_Directions *copie = (Pile_Directions *)malloc(sizeof(Pile_Directions));
    if (copie == NULL)
    {
        printf("Erreur d'allocation mémoire\n");
        return NULL;
    }
    initialiserPileDirections(copie);

    // On parcourt la pile source pour copier les éléments dans l'ordre inverse
    Noeud_Direction *courant = source->sommet;
    Pile_Directions temp;
    initialiserPileDirections(&temp);

    while (courant != NULL)
    {
        empilerDirection(&temp, courant->valeur);
        courant = courant->suivant;
    }

    // On remet dans l'ordre original
    while (!estVidePileDirections(&temp))
    {
        empilerDirection(copie, depilerDirection(&temp));
    }

    return copie;
}
/* ---- Pile de Piles de Directions ---- */

typedef struct Noeud_PileDirections
{
    Pile_Directions *directions;
    struct Noeud_PileDirections *suivant;
} Noeud_PileDirections;

typedef struct
{
    Noeud_PileDirections *sommet;
} Pile_PilesDirections;

/* Initialiser une pile de piles de directions */
void initialiserPilePilesDirections(Pile_PilesDirections *pile)
{
    pile->sommet = NULL;
}

/* Vérifier si une pile de piles de directions est vide */
bool estVidePilePilesDirections(const Pile_PilesDirections *pile)
{
    return pile->sommet == NULL;
}

/* Empiler une pile de directions */
void empilerPileDirections(Pile_PilesDirections *pile, Pile_Directions *directions)
{
    Noeud_PileDirections *nouveau = (Noeud_PileDirections *)malloc(sizeof(Noeud_PileDirections));
    if (nouveau == NULL)
    {
        printf("Erreur d'allocation mémoire\n");
        return;
    }
    nouveau->directions = directions;
    nouveau->suivant = pile->sommet;
    pile->sommet = nouveau;
}

/* Dépiler une pile de directions */
Pile_Directions *depilerPileDirections(Pile_PilesDirections *pile)
{
    if (estVidePilePilesDirections(pile))
    {
        printf("La pile de piles de directions est vide\n");
        return NULL;
    }
    Noeud_PileDirections *temp = pile->sommet;
    Pile_Directions *resultat = temp->directions;
    pile->sommet = temp->suivant;
    free(temp);
    return resultat;
}

/* Libérer une pile de piles de directions */
void libererPilePilesDirections(Pile_PilesDirections *pile)
{
    while (!estVidePilePilesDirections(pile))
    {
        Pile_Directions *liste = depilerPileDirections(pile);
        while (!estVidePileDirections(liste))
        {
            depilerDirection(liste);
        }
        free(liste); // Libérer la mémoire de la pile de directions
    }
}

#endif // PILE_H
