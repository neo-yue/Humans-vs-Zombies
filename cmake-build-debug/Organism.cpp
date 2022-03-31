//
// Created by Administrator on 2021/11/25.
//

#include "Organism.h"
#include "City.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <ratio>
#include "Human.h"

using namespace std;
Organism::Organism() {

}

Organism::~Organism() noexcept {

}



// Create an organism at the given coordinates in the given city.
Organism::Organism(City* aCity, int xCoord, int yCoord) {
    city = aCity;
    x = xCoord;
    y = yCoord;
    spawnTicks = 0;
    moved = false;
    city->setOrganism(x, y, this);
}

// flags the organism as moved or not
void Organism::setMoved(bool hasMoved) {
    moved = hasMoved;
}

// has the organism moved or not?
bool Organism::getMoved() const {
    return moved;
}

// moves the organism from coordinates (x,y) to (xNew,yNew)
void Organism::setPosition(int xNew, int yNew) {

    city->setOrganism(xNew, yNew, city->getOrganism(x, y));

    city->setOrganism(x, y, NULL);

    x = xNew;
    y = yNew;

    city->getOrganism(x, y)->setMoved(true);
}




bool Organism::inRange(int xx, int yy)
{
    return (xx >= 0) && (xx < GRIDSIZE) && (yy >= 0) && (yy < GRIDSIZE);
}


//Load various possible moving directions into vector and then shuffle,
// return 0 when there is no moving direction
Direction Organism::randomMove() {

    vector<int>recruit;
    if(city->getOrganism(x, y + 1) == NULL && inRange(x, y + 1))
    {
        recruit.push_back(UP);
    }

    if(city->getOrganism(x, y - 1) == NULL && inRange(x, y - 1))
    {
        recruit.push_back(DOWN);
    }

    if(city->getOrganism(x - 1, y) == NULL && inRange(x - 1, y))
    {
        recruit.push_back(LEFT);
    }

    if(city->getOrganism(x + 1, y) == NULL && inRange(x + 1, y))
    {
        recruit.push_back(RIGHT);
    }
    if (!recruit.empty()) {

        unsigned seed = chrono::system_clock::now().time_since_epoch().count();//create random seed using system clock
        shuffle(recruit.begin(), recruit.end(), default_random_engine(seed));
    }else {
        return nonDirection;
    }

    return static_cast<Direction>(recruit[0]);
}

