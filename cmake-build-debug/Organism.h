//
// Created by Administrator on 2021/11/25.
//

#ifndef ZOMBIE_ORGANISM_H
#define ZOMBIE_ORGANISM_H

enum OrganismType {HUMAN, ZOMBIE};
enum Direction {UP = 0, DOWN, LEFT, RIGHT,upperLeft,upperRight,lowerLeft,lowerRight,nonDirection};
class City;

class Organism {
protected:
    // This organism's x position in the world.
    int x;

    // This organism's y position in the world.
    int y;

    // The state of organism movement
    bool moved;

    // Number of ticks since spawning.
    int spawnTicks;

    // A pointer to the city in which this organism lives.
    City* city;

    // Sets this organism from coordinates (x,y) to (xNew,yNew).
    void setPosition(int xNew, int yNew);

    //Randomize the direction of movement
    Direction randomMove();

    //Confirm if the creature is in the grid
    bool inRange(int xx, int yy);



public:

    Organism();
    virtual ~Organism();

    // Create an organism at the given coordinates.
    Organism(City* aCity, int xCoord, int yCoord);

    // In the given world moves this organism.
    virtual void move() = 0;

    // Makes this organism spawn.
    virtual void spawn() = 0;

    // Returns the type of this organism.
    virtual OrganismType getSpecies() const = 0;

    // The character representation of this organism.
    virtual char symbol() const = 0;



    // set a flag of this organism as moved or not.
    void setMoved(bool moved);

    // The state of organism movement
    bool getMoved() const;
};



#endif //ZOMBIE_ORGANISM_H
