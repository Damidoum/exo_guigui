#ifndef PILE_H
#define PILE_H

#include "modelisation_robot_labyrinthe.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Liste */

typedef struct Noeud_Liste
{
    Direction direction;
    struct Noeud_Liste *suivant;
} Noeud_Liste;

Noeud_Liste *ajouterDirection(Noeud_Liste *liste, Direction valeur)
{
    Noeud_Liste *nouveau = (Noeud_Liste *)malloc(sizeof(Noeud_Liste));
    if (nouveau == NULL)
    {
        printf("Erreur d'allocation mémoire\n");
        return liste;
    }
    nouveau->direction = valeur;
    nouveau->suivant = liste;
    return nouveau;
}

Noeud_Liste *extraireDirection(Noeud_Liste *liste, Direction *valeur)
{
    if (liste == NULL)
    {
        printf("Liste vide\n");
        *valeur = -1;
        return NULL;
    }
    *valeur = liste->direction;
    Noeud_Liste *temp = liste;
    liste = liste->suivant;
    free(temp);
    return liste;
}

void libererListe(Noeud_Liste *liste)
{
    while (liste != NULL)
    {
        Noeud_Liste *temp = liste;
        liste = liste->suivant;
        free(temp);
    }
}

typedef struct Noeud_Pile
{
    Noeud_Liste *liste;
    struct Noeud_Pile *suivant;
} Noeud_Pile;

typedef struct
{
    Noeud_Pile *sommet;
} Pile;

void initialiserPileListes(Pile *p)
{
    p->sommet = NULL;
}

bool estVidePileListes(Pile *p)
{
    return p->sommet == NULL;
}

void empilerListe(Pile *p, Noeud_Liste *liste)
{
    Noeud_Pile *nouveau = (Noeud_Pile *)malloc(sizeof(Noeud_Pile));
    if (nouveau == NULL)
    {
        printf("Erreur d'allocation mémoire\n");
        return;
    }
    nouveau->liste = liste;
    nouveau->suivant = p->sommet;
    p->sommet = nouveau;
}

Noeud_Liste *depilerListe(Pile *p)
{
    if (estVidePileListes(p))
    {
        printf("La pile de listes est vide\n");
        return NULL;
    }
    Noeud_Pile *temp = p->sommet;
    Noeud_Liste *liste = temp->liste;
    p->sommet = temp->suivant;
    free(temp);
    return liste;
}

void libererPileListes(Pile *p)
{
    while (!estVidePileListes(p))
    {
        Noeud_Liste *liste = depilerListe(p);
        libererListe(liste);
    }
}

#endif // PILE_H
