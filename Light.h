#ifndef __LIGHT_H__
#define __LIGHT_H__

#include <iostream>
using namespace std;

enum class Color {red, yellow, green}
enum class LightDirection {ns,we}

class Light{
  public:
    Light();
    ~Light();
    Light(int redDuration, int yellowDuration, int greenDuration, Color currentLight, LightDirection way);
    Light(const Light& other);

    Color getColor();
    void updateColor(int time);
    int getTimeRemain(int time);
    
  private:
    int redTime;
    int greenTime;
    int yellowTime;
    int cycle;
    Color currentColor;
    LightDirection currentDirection;

};




#endif
