#ifndef __VEHICLE_H__
#define __VEHICLE_H__

#inclue <vector>
#include "VehicleBase.h"

using namespace std;

class Vehicle : public VehicleBase{
  public:
    Vehicle();
    ~Vehicle();
    Vehicle(const Vehicle& other);
    Vehicle(VehicleType type, Direction originalDirection,
            int head_x, int head_y, int back_x, int back_y, bool turnRight);

    VehicleType getVehicleType();
    Direction   getVehicleOriginalDirection();

    int getHeadX();
    int getHeadY();
    vector<int> getHead();

    int getBackX();
    int getBackY();
    vector<int> getBack();

    void setHead(int x, int y);
    void setBack(int x, int y);

    int getSize();

    void advance();

    void turnRight();


  private:
     VehicleType vehicleType;
     int size;
     int headX;
     int headY;
     int backX;
     int backY;
     Direction   vehicleDirection;
     bool willTurnRight;
}

#endif
