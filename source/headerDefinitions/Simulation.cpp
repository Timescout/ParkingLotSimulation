/*  Simulation.cpp
    Parking Lot Simulator
    Andrew Bergman

    Defines the Simulation class.
*/

#include <Simulation.h>

Simulation::Simulation() {}

void Simulation::addBuilding(Building building) { buildings_.push_back(building); }

void Simulation::addenterance(Location enterance) { enterances_.push_back(enterance); }

void Simulation::addParkingStrip(Strip parkingStrip) { parkingStrips_.push_back(parkingStrip); }

void Simulation::generateArrivals()
{
    // set up the generation
    srand(seed_);
    futureEventsList_ = std::priority_queue<Event, std::deque<Event>, EventComparer>(); // empty the queue
    
    // find how many cars need to be generated.
    int totalParkingSpots = 0;
    for (auto i = parkingStrips_.begin(); i != parkingStrips_.end(); i++) 
    { 
        totalParkingSpots += i->getNumberParkingSpots();
    }
    int numCars = parkingOccupancy_ * totalParkingSpots * simulationTime_ / 41; // 41 is expected shopping time.

    // Generate Cars
    cars_ = std::list<Car>(numCars); // clear cars
    std::normal_distribution<TimeLength> shoppingTimeModel(41, 15); // average shopping time is 41 minutes, and I kindof just guessed the standard deviation
    std::uniform_real_distribution<TimeLength> arrivalTimeModel(0, simulationTime_);
    std::default_random_engine generator(seed_); // needed for the normal distribution.
    TimePoint arrivalTime;
    for (auto i = cars_.begin(); i != cars_.end(); i++)
    {
        arrivalTime = arrivalTimeModel(generator);
        TimeLength shoppingTime = shoppingTimeModel(generator);
        Location startLocation = enterances_[rand() % enterances_.size()];
        Location endLocation = enterances_[rand() % enterances_.size()];
        Location buildingenterance =  buildings_[rand() % buildings_.size()].getEntereneces()[0];
        float weightToMe = rand();
        float weightStripToBuilding = rand();
        *i = Car(currentTime_, arrivalTime, shoppingTime, startLocation, endLocation, buildingenterance, weightToMe, weightStripToBuilding);
        
        // generate arrival Events for the Cars.
        addEvent(Event(arrivalTime, i, EventType::Arrive));
    }



}

void Simulation::simulate() 
{
    // setup
    Event currentEvent;
    std::list<Car>::iterator activeCarItr;
    carsInLot = 0;
    outputParameters();
    *output_ << "Cars\n"
             << "Arrival Time,Shopping Time,Distance to me weight,Distance to enterance Weight,enterance Location,Starting Location,Strip number,Spot number,Total Time Driven\n";

    // Main simulation loop.
    while (futureEventsList_.size() > 0)
    {
        // Get the next event from the future events list.
        currentEvent = futureEventsList_.top();
        currentTime_ = currentEvent.eventTime;
        activeCarItr = currentEvent.carItr;
        futureEventsList_.pop();
        //std::cout << "current time: " << currentTime_ << "\n";

        // Act out the next Event.
        switch (currentEvent.eventType)
        {
        case Arrive:
        {
            carsInLot++;
            //std::cout << "Cars in lot: " << carsInLot << "\n";
            // find a parking spot for the car.
            TimeLength searchTime = findParkingSpot(*activeCarItr); // this function will add time to the diveTime of the Car.
            // create a park event.
            futureEventsList_.push(Event(currentTime_ + searchTime, activeCarItr, EventType::Park));
            break;
        }
        case Park:
        {
            // if the parking spot is open, park and create a depart event.
            if (!parkingStrips_[activeCarItr->stripIndex][activeCarItr->spotIndex].occupied)
            {
                //std::cout << "strip index: " << activeCarItr->stripIndex << " spot index: " << activeCarItr->spotIndex << " Parked in.\n";

                parkingStrips_[activeCarItr->stripIndex][activeCarItr->spotIndex].park(currentTime_+activeCarItr->getShoppingTime());
                futureEventsList_.push(Event(currentTime_ + activeCarItr->getShoppingTime(), activeCarItr, EventType::Depart));
            }
            // otherwise find a new spot for the car and add a park event.
            else
            {
                // find a parking spot for the car.
                TimeLength searchTime = findParkingSpot(*activeCarItr); // this function will add time to the diveTime of the Car.
                // create a park event.
                futureEventsList_.push(Event(currentTime_ + searchTime, activeCarItr, EventType::Park));
            }
            break;
        }

        case Depart:
        {
            carsInLot--;
            // The Car leaves the spot.
            //std::cout << "strip index: " << activeCarItr->stripIndex << " spot index: " << activeCarItr->spotIndex << " Departed.\n";
            activeCarItr->addTimeDriven((1/(float)Car::speed) * taxiDistance(activeCarItr->getCurrentLocation(), activeCarItr->getEndLocation()));
            parkingStrips_[activeCarItr->stripIndex][activeCarItr->spotIndex].depart();
            outputCar(*activeCarItr);
            break;
        }
        default:
        {
            break;
        }    
        }
    }
}

void Simulation::addEvent(Event event) 
{
    futureEventsList_.push(event);
}

TimeLength Simulation::findParkingSpot(Car& car)
{
    // Rank all of the parking strips for the car.
    std::vector<std::pair<float, int>> stripsRanked;
    for (int i = 0; i < parkingStrips_.size(); i++)
    {
        Distance distanceCartoStrip = taxiDistance(car.getCurrentLocation(), parkingStrips_[i].getenterance1());
        Distance distanceStripToBuilding = distance(parkingStrips_[i].getenterance1(), car.getBuildingenterance());
        stripsRanked.push_back(std::pair<float, int>(distanceCartoStrip * car.distanceToMeWeight + distanceStripToBuilding * car.distanceToenteranceWeight, i));
    }
    std::sort(stripsRanked.begin(), stripsRanked.end());

    // go through the strips and search for a parking strip.
    bool enterance1 = true;
    TimeLength totalTimeDriven = 0;
    while (true)
    {
        for (int i = 0; i < stripsRanked.size(); i ++)
        {
            // determine which enterance to search for a spot from.
            Location enteranceUsed = enterance1 ? parkingStrips_[stripsRanked[i].second].getenterance1() : parkingStrips_[stripsRanked[i].second].getenterance2();
            // drive to the enterance
            totalTimeDriven += (1/(float)Car::speed) * taxiDistance(car.getCurrentLocation(), enteranceUsed);
            // find the next open spot
            int parkingSpotItr = parkingStrips_[stripsRanked[i].second].getClosestVacantSpot(enteranceUsed, totalTimeDriven); // TODO rename parkingspotItr
            if (parkingSpotItr != -1) // if a spot is found
            {
                Location newLocation = enteranceUsed;
                Location corner1 = parkingStrips_[stripsRanked[i].second].getCorner1();
                Location corner2 = parkingStrips_[stripsRanked[i].second].getCorner2();
                if (abs(corner1.x-corner2.x) > abs(corner1.y - corner2.y))
                {
                    newLocation.x += enterance1 ? parkingStrips_[stripsRanked[i].second][parkingSpotItr].distanceFromenterance1: parkingStrips_[stripsRanked[i].second][parkingSpotItr].distanceFromenterance2 ;
                }
                else
                {
                    newLocation.y += enterance1 ? parkingStrips_[stripsRanked[i].second][parkingSpotItr].distanceFromenterance1: parkingStrips_[stripsRanked[i].second][parkingSpotItr].distanceFromenterance2 ;
                }
                car.setCurrentLocation(newLocation);
                car.stripIndex = stripsRanked[i].second;
                //car.parkingSpotItr_ = parkingSpotItr;
                car.spotIndex = parkingSpotItr;
                Distance distanceDriven = enterance1 ? parkingStrips_[stripsRanked[i].second][parkingSpotItr].distanceFromenterance1 : parkingStrips_[stripsRanked[i].second][parkingSpotItr].distanceFromenterance2;
                //TODO bad, dont do this. \/
                totalTimeDriven += (1/(float)Car::speed) * distanceDriven;
                car.addTimeDriven(totalTimeDriven); // exit
                return totalTimeDriven;
            }
            // if a spot is not found, try the next strip
            enterance1 = !enterance1;
            // add time driven down the strip.
            totalTimeDriven += (1/(float)Car::speed) * distance(parkingStrips_[stripsRanked[i].second].getenterance1(), parkingStrips_[stripsRanked[i].second].getenterance2());
            // set car's current location to the opposite enterance.
            car.setCurrentLocation(enterance1 ? parkingStrips_[stripsRanked[i].second].getenterance1() : parkingStrips_[stripsRanked[i].second].getenterance2());
        }
    }

}

void Simulation::setSeed(int seed) { seed_ = seed; }

void Simulation::setRunTime(TimeLength funTime) { simulationTime_ = funTime; }

void Simulation::setAverageDensity(float averageDensity) { parkingOccupancy_ = averageDensity; }

void Simulation::outputParameters()
{
    *output_ << "seed,simulation Time, parking Occupancy\n"
             << seed_ << "," << simulationTime_ << "," << parkingOccupancy_ << "\n";
    *output_ << "Buildings\n"
             << "enterances\n";
    for (auto i = buildings_.begin(); i != buildings_.end(); i++)
    {
        std::vector<Location> buildingenterances = i->getEntereneces();
        for (auto j = buildingenterances.begin(); j != buildingenterances.end(); j++)
        {
            *output_ << j->x << " " << j->y << ",";
        }
        *output_ << "\n";
    }
    *output_ << "Parking Strips\n"
             << "Corner 1, Corner 2, enterance 1, Enternece 2, Num Parking Spots\n";
    for (auto i = parkingStrips_.begin(); i != parkingStrips_.end(); i++)
    {
        Location corner1 = i->getCorner1();
        Location corner2 = i->getCorner2();
        Location enterance1 = i->getenterance1();
        Location enternece2 = i->getenterance2();
        *output_ << corner1.x << " " << corner1.y << ","
                 << corner2.x << " " << corner2.y << ","
                 << enterance1.x << " " << enterance1.y << ","
                 << enternece2.x << " " << enternece2.y << ","
                 << i->getNumberParkingSpots() << "\n";
    }
    *output_ << "enterances to the Parking Lot\n";
    for (auto i = enterances_.begin(); i != enterances_.end(); i++)
    {
        *output_ << i->x << " " << i->y << "\n";
    }

}

void Simulation::outputCar(Car car) 
{
    *output_ << car.getArrivalTime() << ","
             << car.getShoppingTime() << ","
             << car.distanceToMeWeight << ","
             << car.distanceToenteranceWeight << ","
             << car.getBuildingenterance().x << " " << car.getBuildingenterance().y << ","
             << car.arrivalenterance.x << " " << car.arrivalenterance.y << ","
             << car.stripIndex << ","
             << car.spotIndex << ","
             << car.getTimeDriven() << "\n";
}

void Simulation::setOutputStream(std::ostream& outputStream)
{
    output_ = &outputStream;
}