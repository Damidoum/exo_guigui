#include "interface_simulation_labyrinthe.h"
#include "modelisation_robot_labyrinthe.h"
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

Direction *resoudre_labyrinthe_sans_bifurcation(Position position, Position arrivee, Direction direction)
{
    Tableau solution = {NULL, 0};
    while (position.x != arrivee.x || position.y != arrivee.y)
    {
        direction = determiner_prochaine_direction(&position, direction);
        update_solution(&solution, direction);
        afficher_avancer_labyrinthe(&position, direction);
        avancer(&position, direction);
    }
    if (position.x == arrivee.x && position.y == arrivee.y)
    {
        printf("Le robot a atteint la sortie\n");
    }
    else
    {
        printf("Le robot n'a pas atteint la sortie\n");
    }
    return solution.direction;
}

int main(int argc, char *argv[])
{
    Position position, arrivee;
    Direction direction = initialiser_labyrinthe(SANS_BIFURCATION, &position, &arrivee, 1);
    Direction *solution = resoudre_labyrinthe_sans_bifurcation(position, arrivee, direction);
    free(solution);
}