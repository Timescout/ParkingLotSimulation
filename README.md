This program simulates a parking lot with the goal of comparing driver behavior against how they perform in a crouded parking lot. Drivers arrive at the parking lot, park, idle for a time during which they shop and do other activities, and then they leave. The total distance driven is recorded and output along with driver characteristics into a .csv file. 

intro
Project goals
Simulation outline
    what is a building?
    what is a parking spot?
    what is a strip?
    how do cars behave?
Simulation setup


The simulation is event based which means that it jumps ahead in time to when the next event happens rather than simulate all actions at the same time. During an event the simulation makes decisions based on what type of event it is and the car who the event is occuring to. For example, a car might try to park or arrive in the lot. 

Buildings have enterances and may have one or more. Each car has a building that they want to shop at and some will try to park as close to an enterance of that building as they can. One thing that the simulation will measure is the distance that drivers will have to walk to their desired building. 

A parking spot can be occupied or free. They are organized into parking strips where each strip is wide enough to allow two way traffic and parking spots to line both sides of the strip. A current limitation of the simulation is that strips must have spots on both sides. Strips are defined by setting two opposite corners which creates a rectangle. This rectangle must have either side be 52 and the other must be a multiple of 8 to make sure that the parking spots are created correctly. For example both 52x8 and 8x52 are valid configurations. 

There are two considerations that cars use to determine where to park. Each spot that is vaccant at the time when the car chooses is ranked and the best spot is choosen and driven to. If someone parks in the spot before the car gets there this process is repeated until an empty spot is found. The ranking of each spot is determined by the distance from the spot to the building the car wants to shop at and the distance from the car's current location and the parking spot. Each factor has a weighting unique to each car and is determined randomly.

The overall Simulation has a few variables that need to be given for it to run. In main.cpp you can see how to set these and examples of variables. The first variable is how long to run the simulation. The simulation may run longer than the given time but new cars will not arrive after the given time. The next is the average density. This value is used to control how many cars are in the lot and must be between 0 and 1. Higher values mean more cars will arrive. The next variable is where data will be read from the simulation. In main.cpp the data is output to a .csv file but this could also std::cout or any other ostream object. The last variable you can change is the random seed. Giving the same seed to the simulation will result in the same simulation being run.

To set up a simulation you need to add at least one building, one parking strip, and one enterance. Before running the simulation, make sure to run simulation.generateArrivals().