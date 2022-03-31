//
// Created by Administrator on 2021/11/25.
//


#include "Human.h"


using namespace std;

Human::Human(City* aCity, int xCoord, int yCoord) : Organism(aCity, xCoord, yCoord)
{
    humanCount++;
}

Human::~Human() {

    humanCount--;
}

//Humans move after calling randomMove functions
void Human::move()
{
    spawnTicks++;
    Direction dir=randomMove();
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

//When humans reach the HUMAN_BREED round,
// they will be recruited randomly in the up, down, left, and right directions
void Human::spawn() {
    if (spawnTicks>=HUMAN_BREED ){
        Direction dir=randomMove();
        switch (dir) {
            case UP:
                new Human(city, x, y + 1);
                spawnTicks = 0;
                break;
            case DOWN:
                new Human(city, x, y - 1);
                spawnTicks = 0;
                break;
            case LEFT:
                new Human(city, x - 1, y);
                spawnTicks = 0;
                break;
            case RIGHT:
                new Human(city, x + 1, y);
                spawnTicks = 0;
                break;
            default:
                spawnTicks = 0;
                break;
        }


    }
}


OrganismType Human::getSpecies() const
{

    return HUMAN;
}

//Symbols displayed in the city
char Human::symbol() const
{
    return HUMAN_CH;
}



