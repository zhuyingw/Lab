#include "Light.h"

Light::Light(){
  redTime = -1;
  greenTime = -1;
  yellowTime = -1;
  cycle = -1;
  currentColor = NULL;
  currentDirection = NULL;
}

Light:~Light(){}

Light::Light(int redDuration, int yellowDuration, int greenDuration, Color currentLight, LightDirection way):
redTime{redDuration}, yellowTime{yellowDuration}, greenTime{greenDuration}{
  currentColor = currentLight;
  currentDirection = way;
  cycle = redTime + yellowTime + greenTime;
}

Light::Light(const Light& other){
  redTime = other.redTime;
  yellowTime = other.yellowTime;
  greenTime = other.greenTime;
  cycle = other.cycle;
  currentColor = other.currentColor;
  currentDirection = other.currentDirection;
}

Color Light::getColor(){
  return currentColor;
}

void Light::updateColor(int time){
  int cur = time % cycle;

  switch(direction){
    case LightDirection:ns:
      if (cur >= 0 && cur < greenTime){
        currentColor = Color:green;
      }
      else if(cur >= greenTime && cur < greenTime + yellowTime){
        currentColor = Color:yellow;
      }
      else if(cur >= greenTime + yellowTime){
        currentColor = Color:red;
      }
      break;

    case LightDirection:we:
      if (cur >= 0 && cur < greenTime + yellowTime){
        currentColor = Color:red;
      }
      else if(cur>= greenTime + yellowTime && cur < redTime + greenTime){
        currentColor = Color:green;
      }
      else if(cur>= redTime + greenTime){
        currentColor = Color:yellow;
      }
      break;
    break;
  }

}
