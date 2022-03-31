#include <iostream>
#include "City.h"
#include <chrono>
#include <thread>

using namespace std;

void ClearScreen()
{
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

int main()
{
    City newCity;
    //Set time interval
    chrono:: seconds interval(PAUSE_SECONDS);
    //Print initial city
    cout<<newCity;

    int step=0;
    //Only one species is left or stops after "ITERATIONS" number of times
    do {
        this_thread::sleep_for(interval);
        ClearScreen();
        newCity.simulate();
        cout<<newCity;
        step++;
    }while((newCity.hasDiversity())&&step<ITERATIONS);


    return 0;
}
