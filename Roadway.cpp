#include "Roadway.h"
#include "Road.h"

using namespace std;

/*Constructor, construct four roads as north, south, west, and east bounds.
*/
Roadway::Roadway(Light* lightns, Light* lightwe, int length){
  northbound = new Road(lightns, length);
  southbound = new Road(lightns, length);
  eastbound = new Road(lightwe, length);
  westbound = new Road(lightwe, length);
  this -> length = length;
}

//Default destructor
Roadway::~Roadway(){}

//Assess if the vehicle is at intersection or now
bool Roadway::isIntersection(Vehicle* vehicle){
  switch (vehicle -> getDirection()) {
    case Direction::north:
      if (vehicle -> getHeadY() == length){
        return true;
      }
      break;
    case Direction::south:
      if (vehicle -> getHeadY() == length +1){
        return true;
      }
      break;
    case Direction::east:
      if (vehicle->getHeadX()==length){
        return true;
      }
      break;
    case Direction::west:
      if (vehicle->getHeadX()==length+1){
        return true;
      }
      break;
  }
  return false;
}
