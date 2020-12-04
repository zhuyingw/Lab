#include "Light.h"

//Default constructor, initialize every value to -1
Light::Light(){
  redTime = -1;
  greenTime = -1;
  yellowTime = -1;
  cycle = -1;
}

//Default destuctor
Light::~Light(){}

//Constructor with all light time durations, and the current light with which LightDirection light is on.
Light::Light(int greenDuration, int yellowDuration, int redDuration, Color currentLight, LightDirection way){
  greenTime = greenDuration;
  yellowTime = yellowDuration;
  redTime = redDuration;
  currentColor = currentLight;
  currentDirection = way;
  cycle = redDuration + yellowDuration + greenDuration;
}

//Copy constructor
Light::Light(const Light& other){
  redTime = other.redTime;
  yellowTime = other.yellowTime;
  greenTime = other.greenTime;
  cycle = other.cycle;
  currentColor = other.currentColor;
  currentDirection = other.currentDirection;
}

//Return the current color of the light
Color Light::getColor(){
  return currentColor;
}

//Update the color of the light as time goes on
void Light::updateColor(int time){
  int cur = time % cycle;

  switch(currentDirection){
    case LightDirection::ns:
    //initialize the first light of ns to be green light
      if (cur >= 0 && cur < greenTime){
        currentColor = Color::green;
      }
      else if(cur >= greenTime && cur < greenTime + yellowTime){
        currentColor = Color::yellow;
      }
      else if(cur >= greenTime + yellowTime && cur < cycle){
        currentColor = Color::red;
      }
      break;

    case LightDirection::we:
      if (cur >= 0 && cur < redTime){
        currentColor = Color::red;
      }
      else if(cur>= redTime && cur < redTime + greenTime){
        currentColor = Color::green;
      }
      else if(cur>= redTime + greenTime && cur < cycle){
        currentColor = Color::yellow;
      }
      break;

  }
}

//Get how much time is remained till the light color changes again
  int Light::getTimeRemain(int time){
    int cur = time %cycle;

    switch (currentDirection) {
      case LightDirection::ns:
        if (currentColor == Color::green){
          return greenTime -1 - cur;
        }
        else if (currentColor == Color::yellow){
          return greenTime+yellowTime - 1 - cur;
        }
        else if (currentColor == Color::red){
          return cycle -1 - cur;
        }
      case LightDirection::we:
        if (currentColor == Color::green){
          return redTime+greenTime -1 - cur;
        }
        else if (currentColor == Color::yellow){
          return cycle - 1 - cur;
        }
        else if (currentColor == Color::red){
          return redTime -1 - cur;
        }
  }
    return -1;
}
