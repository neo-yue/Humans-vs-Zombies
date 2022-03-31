//
// Created by Administrator on 2021/11/25.
//

#include "Zombie.h"
#include "Human.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;

Zombie::Zombie(City* aCity, int xCoord, int yCoord) : Organism(aCity, xCoord, yCoord)
{
    starveCount = 0;
    zombieCount++;
}

Zombie::~Zombie() {

    zombieCount--;
}

//The move of zombies includes eating, moving.
void Zombie::move()
{
    spawnTicks++;
    starveCount++;
    Direction eat=randomSpawn();
    switch (eat) {
        case UP:
            setPosition( x, y + 1);
            starveCount = 0;
            break;
        case DOWN:
            setPosition( x , y - 1);
            starveCount = 0;
            break;
        case LEFT:
            setPosition(x - 1, y);
            starveCount = 0;
            break;
        case RIGHT:
            setPosition( x + 1, y);
            starveCount = 0;
            break;
        case upperLeft:
            setPosition(x - 1, y + 1);
            starveCount = 0;
            break;
        case upperRight:
            setPosition( x + 1, y + 1);
            starveCount = 0;
            break;
        case lowerLeft:
            setPosition( x - 1, y - 1);
            spawnTicks=0;
            break;
        case lowerRight:
            setPosition( x + 1, y - 1);
            starveCount = 0;
            break;
        default:
            break;
        }

    if(!moved) {
        Direction dir = randomMove();;
        switch (dir) {
            case UP:
                setPosition(x, y + 1);
                break;
            case DOWN:
                setPosition(x, y - 1);
                break;
            case LEFT:
                setPosition(x - 1, y);
                break;
            case RIGHT:
                setPosition(x + 1, y);
                break;
            default:
                break;
        }
    }






}

//When the zombies are breeding, remove the original humans and spawn a new zombie
void Zombie::spawn()
{
    if(spawnTicks >= ZOMBIE_BREED)
    {
        Direction convert=randomSpawn();

        switch (convert) {
            case UP:
                city->setOrganism(x, y + 1,NULL);
                new Zombie(this->city, x, y + 1);
                spawnTicks = 0;
                break;
            case DOWN:
                city->setOrganism(x , y - 1,NULL);
                new Zombie(this->city, x , y - 1);
                spawnTicks = 0;
                break;
            case LEFT:
                city->setOrganism(x - 1, y,NULL);
                new Zombie(this->city, x - 1, y);
                spawnTicks = 0;
                break;
            case RIGHT:
                city->setOrganism(x + 1, y,NULL);
                new Zombie(this->city, x + 1, y);
                spawnTicks = 0;
                break;
            case upperLeft:
                city->setOrganism(x - 1, y + 1,NULL);
                new Zombie(this->city, x - 1, y + 1);
                spawnTicks = 0;
                break;
            case upperRight:
                city->setOrganism(x + 1, y + 1,NULL);
                new Zombie(this->city, x + 1, y + 1);
                spawnTicks = 0;
                break;
            case lowerLeft:
                city->setOrganism(x - 1, y - 1,NULL);
                new Zombie(this->city, x - 1, y - 1);
                spawnTicks=0;
                break;
            case lowerRight:
                city->setOrganism(x + 1, y - 1,NULL);
                new Zombie(this->city, x + 1, y - 1);
                spawnTicks = 0;
                break;
            default:
                break;
        }
    }
}

void Zombie::starve() {
    if(starveCount >=ZOMBIE_STARVE ){
        city->setOrganism(x, y,NULL);
        new Human(this->city, x, y);

    }

}



OrganismType Zombie::getSpecies() const
{
    return ZOMBIE;
}


char Zombie::symbol()const
{
    return ZOMBIE_CH ;
}


//Load various possible spawning directions into vector and then shuffle,
// return 0 when there is no moving direction
Direction Zombie::randomSpawn() {

    vector<int>eatDir;
    if (city->getOrganism(x, y + 1) != NULL && city->getOrganism(x, y + 1)->getSpecies() == HUMAN)
    {
        eatDir.push_back(UP);
    }
     if (city->getOrganism(x, y - 1) != NULL && city->getOrganism(x, y - 1)->getSpecies() == HUMAN)
    {
        eatDir.push_back(DOWN);
    }
   if (city->getOrganism(x - 1, y) != NULL && city->getOrganism(x - 1, y)->getSpecies() == HUMAN)
    {
        eatDir.push_back(LEFT);
    }
    if (city->getOrganism(x + 1, y) != NULL && city->getOrganism(x + 1, y)->getSpecies() == HUMAN)
    {
        eatDir.push_back(RIGHT);
    }
     if (city->getOrganism(x - 1, y + 1) != NULL && city->getOrganism(x - 1, y + 1)->getSpecies() == HUMAN)
    {
        eatDir.push_back(upperLeft);
    }
   if (city->getOrganism(x + 1, y + 1) != NULL && city->getOrganism(x + 1, y + 1)->getSpecies() == HUMAN)
    {
        eatDir.push_back(upperRight);
    }

   if (city->getOrganism(x - 1, y - 1) != NULL && city->getOrganism(x - 1, y - 1)->getSpecies() == HUMAN)
    {
        eatDir.push_back(lowerLeft);
    }

    if (city->getOrganism(x + 1, y - 1) != NULL && city->getOrganism(x + 1, y - 1)->getSpecies() == HUMAN)
    {
        eatDir.push_back(lowerRight);
    }



    if (!eatDir.empty()) {

        unsigned seed = chrono::system_clock::now().time_since_epoch().count();//create random seed using system clock
        shuffle(eatDir.begin(), eatDir.end(), default_random_engine(seed));
    }else {
        return nonDirection;
    }

    return static_cast<Direction>(eatDir[0]);
}

