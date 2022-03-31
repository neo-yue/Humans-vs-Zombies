//
// Created by Administrator on 2021/11/25.
//

#ifndef ZOMBIE_CITY_H
#define ZOMBIE_CITY_H

#include <iostream>
#include "GameSpecs.h"
#include "Organism.h"
using namespace std;
class City
{
private:
    // The grid in which the organisms live.
    Organism* grid[GRIDSIZE][GRIDSIZE];

    // Randomly create `count` many organisms of type `orgType`.  This
    // method uses the parameterized constructor in Human and Zombie.
    void createOrganisms(OrganismType orgType, int count);

    // Reset all organisms to not moved.
    void resetOrganisms();

    // Make every organism in this world of type aType move(Zombie could eat and starve).
    void moveOrganism(OrganismType aType);

    // Make every organism in this world spawn.
    void spawnOrganisms();

    //Detect if the zombie is hungry, and if it is, it will change back to a human
    void starveOrganisms();

    //Set the display color of zombie and human symbols
    void Col(int c) const;

    //Number of humans
    int Humans ;

    //Number of Zombies
    int Zombies;

    //Number of simulate times
    int roundTimes;



public:
    // Constructor: creates and initializes this world.
    //Randomly generate zombies and humans
    City();

    // Destructor.
    ~City();


    // Returns the organism at the given coordinates.
    Organism* getOrganism(int x, int y) const;

    // Sets the organism org at position (x,y).
    void setOrganism(int x, int y, Organism* org);

    //Simulate the movement and spawn of organisms
    void simulate();

    //Detect whether humans and zombies coexist
    bool hasDiversity();

    //overload << for print city
    friend ostream& operator<<( ostream &output, City &city );

    //Return the number of humans and zombies, it is not necessary,
    // if you want to test, please cancel the comment
    //int countType(OrganismType aType);
};

#endif //ZOMBIE_CITY_H
