#ifndef __ROAD_H__
#define __ROAD_H__

#include "Light.h"
#include "Vehicle.h"
#include <algorithm>

using namespace std;

class Road{
  public:
    vector<Vehicle*> road;
    Road(Light* lght, int lngth);
    ~Road();

    void addVehicle(Vehicle* vehicle);
    void removeVehicle();
    void removeVehicle(int index);
    void insertTurn(Vehicle* vehicle);

    bool canTurn(Vehicle* vehicle, int time, int yellowTime);
    bool canAdvance(Vehicle* vehicle, int index, int time, int yellowTime);
    bool notFull(Vehicle* vehicle);

    vector<VehicleBase*> forAnimator();

  private:
    Light* light;
    int length;
};

#endif
