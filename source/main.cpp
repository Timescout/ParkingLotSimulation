/*  main.cpp
    Andrew Bergman

    main function and simulation setup.
*/

#include <iostream>
#include <fstream>
#include <Simulation.h>

int main()
{
    
    std::ofstream dataFile;
    dataFile.open("./Data/demoTest.csv");

    Simulation simulation;
    simulation.setRunTime(1440); // set simulation for a full day.
    simulation.setAverageDensity(.95);
    simulation.setOutputStream(dataFile);
    // add 4 buildings to the simulation
    for (int i = 0; i < 4; i++)
    {
        simulation.addBuilding(Building(Location(50, 52*(i+1)-26)));
    }
    int numSpots = 16; // number of spots per side of strip
    // add 4 strips to the parking lot
    for (int i = 0; i < 4; i++)
    {
        Strip strip(Location(20, 52 * i), Location( 20 + 8 *numSpots, 52*(i+1)));
        strip.setEnterance1(Location(20,  52 * i + 26));
        strip.setEnterance2(Location(20 + 8 *numSpots,  52*(i+1)-26));
        simulation.addParkingStrip(strip);
    }
    // add 4 enterances to the parking lot
    simulation.addEnterance(Location(10, 0));
    simulation.addEnterance(Location(10, 52*4));
    simulation.addEnterance(Location(20 + 8*numSpots + 10, 0));
    simulation.addEnterance(Location(20 + 8*numSpots + 10, 52*4));
    // generate the cars!
    simulation.setSeed(17);
    simulation.generateArrivals();

    simulation.simulate();

    dataFile.close();
    
    return 0;
}