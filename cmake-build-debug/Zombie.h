//
// Created by Administrator on 2021/11/25.
//

#ifndef ZOMBIE_ZOMBIE_H
#define ZOMBIE_ZOMBIE_H

#include <iostream>

#include "City.h"
#include "Organism.h"

class Zombie : public Organism
{
public:

    Zombie(City* aCity, int xCoord, int yCoord);
    ~Zombie();

    // In the given world moves this organism.
    void move();

    // Makes this organism spawn.
    void spawn();

    // Returns the type of this organism.
    OrganismType getSpecies() const;

    // The character representation of this organism.
    char symbol() const;

    // Returns true if organism is dead, false otherwise.
    //bool isDead() const;

    Direction randomSpawn();

    //Zombies transformed into humans due to starve
    void starve();


private:

    //Record the zombies hungry for a few rounds
    int starveCount;

    int zombieCount=0;
};





#endif //ZOMBIE_ZOMBIE_H
