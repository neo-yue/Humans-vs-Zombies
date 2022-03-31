//
// Created by Administrator on 2021/11/25.
//

#include "City.h"
#include <iostream>
#include <cstdlib>  // for rand
#include "Human.h"
#include "Zombie.h"
#include <thread>
#include <ctime>
#include <ratio>
#include <windows.h>



using namespace std;

// Public functions


// Default constructor: creates and initializes the city
// the seed is used for seeding the random behaviour.
City::City() {
    //reset rounds
    roundTimes=0;

    // seed the random generator
    srand((unsigned)time(NULL));

     //Create an empty city
    for (int i = 0; i < GRIDSIZE; i++) {
        for (int j = 0; j < GRIDSIZE; j++) {
            grid[i][j] = NULL;
        }
    }

    // creates Humans
    createOrganisms(HUMAN, HUMAN_STARTCOUNT);

    // creates the Zombies
    createOrganisms(ZOMBIE, ZOMBIE_STARTCOUNT);
}

// Deallocate memory allocated to organisms in this world.
City::~City() {
    for (int i = 0; i < GRIDSIZE; i++) {
        for (int j = 0; j < GRIDSIZE; j++) {
            if (grid[i][j] != NULL) {
                delete grid[i][j];
            }
        }
    }
}

// Return the organism at the given coordinates
// If the coordinates are not valid, returns NULL
Organism* City::getOrganism(int x, int y) const {
    if ((x >= 0) && (x <GRIDSIZE) && (y >= 0) && (y <GRIDSIZE)) {
        return grid[x][y];
    } else {
        return NULL;
    }
}

// Sets the entry at x,y to the value passed in.
void City::setOrganism(int x, int y, Organism* org) {
    if ((x >= 0) && (x <GRIDSIZE) && (y >= 0) && (y <GRIDSIZE)) {
        grid[x][y] = org;
    }
}



void City::simulate() {
    roundTimes++;
    // Reset all organisms to not moved
    resetOrganisms();

    // Move the Zombie. ps:include eat and starve.
    moveOrganism(ZOMBIE);

    // Move the Human
    moveOrganism(HUMAN);

    // spawn
    spawnOrganisms();

    //Zombie starving
    starveOrganisms();


}



// Private functions


void City::createOrganisms(OrganismType orgType, int count) {
    int orgCount = 0;
    while (orgCount < count) {
        int x=rand() % GRIDSIZE;
        int y = rand() % GRIDSIZE;
        // Only put ant in empty spot
        if (grid[x][y] == NULL) {
            orgCount++;
            if (orgType == HUMAN) {
                new Human(this, x, y);   // Create a Human and put it into the world
            }
            else if (orgType == ZOMBIE) {
                new Zombie(this, x, y);   // Create a Zombie and put it into the world
            }
        }
    }
}

// Reset all organisms to not moved
void City::resetOrganisms() {
    for(int i = 0; i < GRIDSIZE; i++)
    {
        for (int j = 0; j < GRIDSIZE; j++)
        {
            if(grid[i][j] != NULL)
            {
                grid[i][j]->setMoved(false);
            }
        }
    }
}

// Move all organisms of type aType
void City::moveOrganism(OrganismType aType) {
    for(int i = 0; i < GRIDSIZE; i++)
    {
        for(int j = 0; j < GRIDSIZE; j++)
        {
            if(grid[i][j] != NULL)
            {
                if(grid[i][j]->getSpecies() == aType && !(grid[i][j]->getMoved()))
                {
                    grid[i][j]->move();
                }
            }
        }
    }
}

// Make the organisms breed
void City::spawnOrganisms() {
    for(int i = 0; i < GRIDSIZE; i++)
    {
        for(int j = 0; j < GRIDSIZE; j++)
        {
            if(grid[i][j] != NULL)
            {
                grid[i][j]->spawn();

            }

        }
    }
}


//Call the starve function in the zombie class after down casting
void City::starveOrganisms() {
    for(int i = 0; i < GRIDSIZE; i++)
    {
        for(int j = 0; j < GRIDSIZE; j++)
        {
            if(grid[i][j] != NULL&& grid[i][j]->getSpecies()==ZOMBIE)
            {
                Zombie *starving=dynamic_cast<Zombie*>(grid[i][j]);
                starving->starve();

            }

        }
    }
}

void City::Col(int c) const {

    HANDLE hConsole;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, c);

    return;

}

ostream& operator<<(ostream& output,City& e ){
    e.Humans=0;
    e.Zombies=0;
    output << endl << endl;
    for (int j = 0; j < GRIDSIZE; j++) {
        for (int i = 0; i < GRIDSIZE; i++) {
            if (e.grid[i][j] == NULL) {

                output << SPACE_CH;
            } else {
                if (e.grid[i][j]->getSpecies() == HUMAN) {
                    e.Humans++;
                    e.Col(HUMAN_COLOR);
                    output << e.grid[i][j]->symbol();
                }
                else if (e.grid[i][j]->getSpecies() == ZOMBIE) {
                    e.Zombies++;
                    e.Col(ZOMBIE_COLOR);
                    output << e.grid[i][j]->symbol();
                }
                e.Col(7);
            }
        }
        output << endl;
    }
     output<< "Humans: " << e.Humans << " Zombies: " << e.Zombies;
     output<< " Rounds : "<<e.roundTimes<<endl;
    return output;

}

bool City::hasDiversity() {
    if(Humans==0 || Zombies==0)
    return false;
    else
        return true;
}


//int City::countType(OrganismType aType)
//{
//    if (aType==HUMAN)
//        return Humans;
//    else if (aType==ZOMBIE)
//        return Zombies;
//    else
//        return 0;
//}