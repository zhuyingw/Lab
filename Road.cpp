#include "Road.h"

//Constructor with light and length of the road
Road::Road(Light* lght, int lngth){
  light = lght;
  length = lngth;
}

Road::~Road(){}

void Road::addVehicle(Vehicle* vehicle){
  if (notFull(vehicle)){
    road.push_back(vehicle);
  }
}

//Remove the vehicle from the lane
void Road::removeVehicle(){
  if (road.size() == 0){
    return;
  }
  Vehicle* first_v = road[0];
  switch (first_v -> getDirection()) {
    //check if the vehicle has reached the end of the road
    case Direction::north:
      if (first_v -> getHeadY() > length *2 + 1){
        road.erase(road.begin());
      }
      break;
    case Direction::south:
      if (first_v -> getHeadY() < 0){
        road.erase(road.begin());
      }
      break;
    case Direction::east:
      if (first_v -> getHeadX() > length *2 + 1){
        road.erase(road.begin());
      }
      break;
    case Direction::west:
      if (first_v -> getHeadX() < 0){
        road.erase(road.begin());
      }
      break;
  }

}

//remove vehicle in a specific position on the road
void Road::removeVehicle(int index){
  road.erase(road.begin() + index);
}


//add vehicle when it made a right turn
void Road::insertTurn(Vehicle* vehicle){
  int num = -1;
  switch (vehicle -> getDirection()) {
    case Direction::north:
      for (int i = 0; i < road.size(); i++){
        if (road[i] -> getHeadY() <= length){
          num = i;
          break;
        }
      }
      break;
    case Direction::south:
      for (int i = 0; i < road.size(); i++){
        if (road[i] -> getHeadY() >= length+2){
          num = i;
          break;
        }
      }
      break;
    case Direction::east:
      for (int i = 0; i < road.size(); i++){
        if(road[i] -> getHeadX() <= length){
          num = i;
          break;
        }
      }
      break;
    case Direction::west:
      for (int i =0; i < road.size(); i++){
        if (road[i] -> getHeadX() >= length + 2){
          num = i;
          break;
        }
      }
      break;
  }

// if num is -1, it means there is nothing before this current vehicle we have
  if (num != -1){
    road.insert(road.begin() + num, vehicle);
  }
  else{
    road.push_back(vehicle);
  }
}

/*This assess if there is enough time for the vehicle to make right turn.
If there is not, return false */
bool Road::canTurn(Vehicle* vehicle, int time, int yellowTime){
  int t = 0;

  if (vehicle -> turnOr()){
    t = vehicle -> getSize() + 1;
  }
  else{
    t = vehicle -> getSize() + 2;
  }

  if (light -> getColor() == Color::yellow){
    if (t> light->getTimeRemain(time)){
      return false;
    }
  }

  else if (light -> getColor() == Color::green){
    if (t > light-> getTimeRemain(time) + yellowTime){
      return false;
    }
  }
  return true;

}

//Acess if there is a car in the front, and if there is, can advance or not
bool Road::canAdvance(Vehicle* vehicle, int index, int time, int yellowTime){
  //if first in lane then nothing to worry about but the traffic light
  if(index == 0){

    switch (vehicle ->getDirection()){
      case Direction::north:
        if (vehicle->getHeadY() == length -1){
          if (!canTurn(vehicle,time,yellowTime) || light -> getColor() == Color::red){
            return false;
          }
        }
        break;
      case Direction::south:
        if (vehicle -> getHeadY() == length + 2){
          if (!canTurn(vehicle,time,yellowTime) || light -> getColor() == Color::red){
            return false;
          }
        }
      break;
      case Direction::east:
        if(vehicle -> getHeadX() == length -1){
          if (!canTurn(vehicle,time,yellowTime) || light -> getColor() == Color::red){
            return false;
          }
        }
          break;
          case Direction::west:
            if (vehicle -> getHeadX() == length + 2){
              if (!canTurn(vehicle,time,yellowTime) || light -> getColor() == Color::red){
                return false;
              }
            }
          break;
    }
    return true;
  }

  // if not the first in lane, then don't crash the previous vehicle
  Vehicle* prev_v = road[index-1];
  switch (prev_v -> getDirection()) {
    case Direction::north:
      if(prev_v -> getBackY() -1 == vehicle -> getHeadY()){
        return false;
      }
      else if (vehicle->getHeadY() == length -1){
        if(!canTurn(vehicle,time,yellowTime) || light -> getColor() == Color::red){
          return false;
      }
    }
      break;
    case Direction::south:
      if(prev_v -> getBackY() +1 == vehicle -> getHeadY()){
        return false;
      }
      else if(vehicle -> getHeadY() == length + 2){
        if(!canTurn(vehicle,time,yellowTime) || light -> getColor() == Color::red){
          return false;
        }
      }
      break;
    case Direction::east:
      if (prev_v -> getBackX() - 1 == vehicle -> getHeadX()){
        return false;
      }
      else if(vehicle -> getHeadX() == length -1){
        if (!canTurn(vehicle,time,yellowTime) || light -> getColor() == Color::red){
          return false;
      }
    }
      break;
    case Direction::west:
      if (prev_v -> getBackX() + 1 == vehicle ->getHeadX()){
        return false;
      }
      else if (vehicle -> getHeadX() == length + 2){
        if (!canTurn(vehicle,time,yellowTime) || light -> getColor() == Color::red){
          return false;
        }
      }
      break;
    }
    return true;
}


// return the boolean value if the road is full or not
bool Road::notFull(Vehicle* vehicle){
  if (road.size() == 0){
    return true;
  }

  Vehicle* last_v = road.back();

  switch(last_v -> getDirection()){
    case Direction::north:
      if (last_v -> getBackY() < vehicle->getSize()){
        return false;
      }
    case Direction::south:
      if (last_v -> getBackY() > length * 2 + 1 - (vehicle->getSize())){
        return false;
      }
    case Direction::east:
      if (last_v -> getBackX() < vehicle->getSize()){
        return false;
      }
    case Direction::west:
      if (last_v -> getBackX() > length * 2 + 1 - vehicle->getSize()){
        return false;
      }
  }
  return true;
}

//this is beacause the Animator class requires vecotr of vehicle pointers with size 2length + 2.
vector<VehicleBase*> Road::forAnimator(){
  vector<VehicleBase*> ptr(2*length + 2, nullptr);
  if (road.size() ==0){
    return ptr;
  }
  Vehicle* first = road[0];

  vector<Vehicle*>::iterator it;
  switch (first -> getDirection()) {
    case Direction::north:
      for (it = road.begin(); it != road.end(); it++){
        Vehicle* v = *it;
        for(int i = v -> getBackY(); i <= v-> getHeadY(); i++){
          ptr[i] = v;
        }
      }
      break;
    case Direction::south:
      for (it = road.begin(); it != road.end(); it++){
        Vehicle* v = *it;
        for(int i = v -> getHeadY(); i <= v-> getBackY(); i++){
          ptr[i] = v;
        }
      }
    //reverse the vector becasue of the way set in Animator class
      reverse(ptr.begin(),ptr.end());
      break;
    case Direction::east:
      for (it = road.begin(); it != road.end(); it++){
        Vehicle* v = *it;
        for(int i = v -> getBackX(); i <= v-> getHeadX(); i++){
          ptr[i] = v;
        }
      }
    break;
    case Direction::west:
      for (it = road.begin(); it != road.end(); it++){
        Vehicle* v = *it;
        for(int i = v -> getHeadX(); i <= v-> getBackX(); i++){
          ptr[i] = v;
        }
      }
      reverse(ptr.begin(),ptr.end());
      break;
  }
  return ptr;
}
