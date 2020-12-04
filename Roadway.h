#ifndef __ROADWAY_H__
#define __ROADWAY_H__

#include "Road.h"
#include "Light.h"

using namespace std;

class Roadway{
  public:
    Road* northbound;
    Road* southbound;
    Road* eastbound;
    Road* westbound;
    int length;

    Roadway(Light* lightns, Light* lightwe, int length);
    ~Roadway();
    bool isIntersection(Vehicle* vehicle);
};

#endif
