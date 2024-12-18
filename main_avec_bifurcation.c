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

Pile_Directions lister_directions_possibles(Position *position, Direction direction)
{
    Pile_Directions directions_possibles;
    initialiserPileDirections(&directions_possibles);
    for (int i = 0; i < 4; i++)
    {
        if (est_voie_libre(position, i) && i != direction_opposee(direction))
        {
            empilerDirection(&directions_possibles, i);
        }
    }
    return directions_possibles;
}

Pile_Directions explorer(Position *position, Pile_Directions *directions_a_explorer, Pile_Directions *chemin, Pile_PilesDirections *chemins_a_voir)
{
    Direction direction_a_explorer = depilerDirection(directions_a_explorer);
    empilerDirection(chemin, direction_a_explorer);

    // On empile une copie indépendante des directions restantes
    Pile_Directions *copie_directions = copierPileDirections(directions_a_explorer);
    if (copie_directions != NULL)
    {
        empilerPileDirections(chemins_a_voir, copie_directions);
    }

    afficher_avancer_labyrinthe(position, direction_a_explorer);
    avancer(position, direction_a_explorer);
    return lister_directions_possibles(position, direction_a_explorer);
}

Pile_Directions revenir(Position *position, Pile_Directions *directions_a_explorer, Pile_Directions *chemin, Pile_PilesDirections *chemins_a_voir)
{
    Direction derniere_direction = depilerDirection(chemin);
    afficher_avancer_labyrinthe(position, direction_opposee(derniere_direction));
    avancer(position, direction_opposee(derniere_direction));

    // On récupère la prochaine pile de directions à explorer
    Pile_Directions *nouvelles_directions = depilerPileDirections(chemins_a_voir);
    return *nouvelles_directions;
}

Pile_Directions resoudre_labyrinthe_avec_bifurcation(Position position, Position arrivee, Direction direction)
{
    Pile_Directions chemin;
    initialiserPileDirections(&chemin);
    Pile_PilesDirections chemins_a_voir;
    initialiserPilePilesDirections(&chemins_a_voir);
    Pile_Directions directions_a_explorer = lister_directions_possibles(&position, direction);
    while (position.x != arrivee.x || position.y != arrivee.y)
    {
        if (!estVidePileDirections(&directions_a_explorer))
        {
            directions_a_explorer = explorer(&position, &directions_a_explorer, &chemin, &chemins_a_voir);
        }
        else
        {
            directions_a_explorer = revenir(&position, &directions_a_explorer, &chemin, &chemins_a_voir);
        }
    }
    return chemin;
}

int main(int argc, char *argv[])
{
    Position position, arrivee;
    Direction direction = initialiser_labyrinthe(SANS_BOUCLE, &position, &arrivee, 1);
    Pile_Directions chemin = resoudre_labyrinthe_avec_bifurcation(position, arrivee, direction);
    return 0;
}