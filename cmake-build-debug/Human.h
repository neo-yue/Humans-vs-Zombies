//
// Created by Administrator on 2021/11/25.
//

#ifndef ZOMBIE_HUMAN_H
#define ZOMBIE_HUMAN_H

#include <iostream>
#include "Organism.h"
#include "City.h"

class Human : public Organism
{
public:

    Human(City* aCity, int xCoord, int yCoord);

    virtual ~Human();

    // In the given world moves this organism.
    void move();

    // Makes this organism spawn.
    void spawn();

    // Returns the type of this organism.
    OrganismType getSpecies() const;

    // The character representation of this organism.
    char symbol() const;



private:
    int humanCount=0;

};




#endif //ZOMBIE_HUMAN_H
