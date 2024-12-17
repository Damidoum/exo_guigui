#include "interface_simulation_labyrinthe.h"
#include "modelisation_robot_labyrinthe.h"
#include "pile.h"
#include <stdio.h>
#include <stdlib.h>

void avancer(Position *position, Direction direction)
{
    if (direction == NORD)
    {
        position->y++;
    }
    else if (direction == SUD)
    {
        position->y--;
    }
    else if (direction == EST)
    {
        position->x++;
    }
    else if (direction == OUEST)
    {
        position->x--;
    }
}

Direction determiner_prochaine_direction(Position *position, Direction direction)
{
    Direction priorites[4][3] = {
        {EST, NORD, OUEST},  // si la direction est nord
        {OUEST, SUD, EST},   // si la direction est sud
        {SUD, EST, NORD},    // ... est
        {NORD, OUEST, SUD}}; // ... ouest

    for (int i = 0; i < 3; i++)
    {
        if (est_voie_libre(position, priorites[direction][i]))
        {
            return priorites[direction][i];
        }
    }

    return direction;
}

Direction direction_opposee(Direction direction)
{
    if (direction == NORD)
    {
        return SUD;
    }
    else if (direction == SUD)
    {
        return NORD;
    }
    else if (direction == EST)
    {
        return OUEST;
    }
    else if (direction == OUEST)
    {
        return EST;
    }
    else
    {
        printf("Direction inconnue\n");
        return -1;
    }
}

Noeud_Liste *lister_direction_possibles(Position position, Direction direction)
{
    Noeud_Liste *liste = NULL;
    Direction direction_op = direction_opposee(direction);
    for (int i = 0; i < 4; i++)
    {
        if (est_voie_libre(&position, i) && i != direction_op)
        {
            liste = ajouterDirection(liste, i);
        }
    }
    return liste;
}
void explorer(Position *position,
              Noeud_Liste *directions_possibles,
              Pile *directions_suivies,
              Pile *listes_restantes)
{
    direction_a_explorer = extraireDirection(directions_possibles, &direction);
}

Direction direction_opposee(Direction direction)
{
    if (direction == NORD)
    {
        return SUD;
    }
    else if (direction == SUD)
    {
        return NORD;
    }
    else if (direction == EST)
    {
        return OUEST;
    }
    else if (direction == OUEST)
    {
        return EST;
    }
}

void update_solution(Tableau *solution, Direction nouvelle_direction)
{
    if (solution->longueur_solution == 0)
    {
        solution->direction = (Direction *)malloc(sizeof(Direction));
        solution->longueur_solution++;
        solution->direction[0] = nouvelle_direction;
    }
    else
    {
        solution->direction = (Direction *)realloc(solution->direction, (solution->longueur_solution + 1) * sizeof(Direction));
        solution->direction[solution->longueur_solution] = nouvelle_direction;
        solution->longueur_solution++;
    }
}

int main(int argc, char *argv[])
{
    // Position position, arrivee;
    // Direction direction = initialiser_labyrinthe(SANS_BIFURCATION, &position, &arrivee, 1);
    return 0;
}