#ifndef __VEHICLE_CPP__
#define __VEHICLE_CPP__

#inclue "Vehicle.h"

Vehicle::Vehicle(){
  vehicleType = VehicleType::car;
  size = -1;
  headX = -1;
  headY = -1;
  backX = -1;
  backY = -1;
  vehicleDirection = Direction::north;
  willTurnRight = false;
}

Vehicle::~Vehicle(){}

Vehicle::Vehicle(const Vehicle& other) : VehicleBase(other){
  size = other.size;
  headX = other.headX;
  headY = other.headY;
  backX = other.backX;
  backY = other.backY;
  willTurnRight = other.willTurnRight;
}

Vehicle::Vehicle(VehicleType type, Direction originalDirection,
          int head_x, int head_y, int back_x, int back_y, bool turnRight)
          : VehicleBase(type, originalDirection){
            if (type == Vehicle::car){
              size = 2;
            }
            else if (type == Vehicle::suv){
              size = 3;
            }
            else if (type == Vehicle::truck){
              size = 4;
            }
            else size = -1;

            headX = head_x;
            headY = head_y;
            backX = back_x;
            backY = back_y;
            willTurnRight = turnRight;
}

VehicleType Vehicle::getVehicleType(){}
Direction Vehicle::getDirection() {}


// not necessary this part
int Vehicle::getHeadX(){
  return headX;
}

int Vehicle::getHeadY(){
  return headY;
}


int Vehicle::getBackX(){
  return backX;
}

int Vehicle::getBackY(){
  return backY;
}
// maybe

vector<int> Vehicle::getHead(){
  vector<int> headPos;

  headPos.push_back(headX);
  headPos.push_back(headY);
}

vector<int> Vehicle::getBack(){
  vector<int> backPos;

  backPos.push_back(backX);
  backPos.push_back(backY);
}

void Vehicle::setHead(int x, int y){
  headX = x;
  headY = y;
}

void Vehicle::setBack(int x, int y){
  backX = x;
  backY = y;
}

int Vehicle::getSize() {

    return size;
}

bool Vehicle::turnRight() {

    return willTurnRight;
}

void Vehicle::advance(){
  if (vehicleDirection == Direction::north){
    headY +=1;
    backY +=1;
  }
  else if (vehicleDirection == Direction::south){
    headY -=1;
    backY -=1;
  }
  else if (vehicleDirection == Direction::west){
    headX -=1;
    backX -=1;
  }
  else if (vehicleDirection == Direction::east){
    headX +=1;
    backX +=1;
  }
}

void Vehicle::turnRight(){
  if (vehicleDirection == Direction::north){
    backY = headY;
    headX += size -1;
    vehicleDirection = Direction::east;
  }
  else if (vehicleDirection == Direction::south){
      backY = headY;
      headX -= size -1;
      vehicleDirection = Direction::west;
  }
  else if (vehicleDirection == Direction::east){
        backX = headX;
        headY -= size -1;
        vehicleDirection = Direction::south;
  }
  else if (vehicleDirection == Direction::west){
        backX = headX;
        headY += size -1;
        vehicleDirection = Direction::north;
  }
}

#endif
