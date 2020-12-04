#ifndef __VEHICLE_H__
#define __VEHICLE_H__

#include <vector>
#include "VehicleBase.h"

using namespace std;

class Vehicle : public VehicleBase{
  public:
    Vehicle();
    ~Vehicle();
    Vehicle(const Vehicle& other);
    Vehicle(VehicleType type, Direction direction,
            int head_x, int head_y, int back_x, int back_y, bool turnRight);

    //VehicleType getVehicleType();
    Direction   getDirection();

    int getHeadX();
    int getHeadY();

    int getBackX();
    int getBackY();

    int getSize();

    void advance();

    void turnRight();
    bool turnOr();


  private:
     VehicleType vehicleType;
     int size;
     int headX;
     int headY;
     int backX;
     int backY;
     Direction   vehicleDirection;
     bool willTurnRight;
};

#endif
