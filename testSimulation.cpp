#include "Vehicle.h"
#include "Light.h"
#include "Roadway.h"
#include "Animator.h"
#include "VehicleBase.h"

#include <iostream>
#include <string>
#include <array>
#include <fstream>
#include <sstream>
#include <iostream>
#include <random>
#include <cstring>


using namespace std;

int main(int argc, char* argv[]){
  // input file read and extract information for initialization later

  ifstream in;

  in.open(argv[1]);

  if(in.bad()){
    cout <<"Input File is not right" <<endl;
  }
  else{
  // set up inital seed
  int initialSeed = atoi(argv[2]); // convert seed from char* to int and save as seed
  //int initialSeed = 8675309;


  //varibale initialization
  // MANUAL SO FAR, NEED TO CHANGE LATER
  int maximum_simulated_time=                 1000;
  int number_of_sections_before_intersection=   10;
  int green_north_south=                        12;
  int yellow_north_south=                        3;
  int green_east_west=                          10; //12
  int yellow_east_west=                          3;
  int red_north_south = green_east_west + yellow_east_west;
  int red_east_west = green_north_south + yellow_north_south;
  double prob_new_vehicle_northbound=               0.25; //0.1
  double prob_new_vehicle_southbound=               0.1;
  double prob_new_vehicle_eastbound=                0.15;
  double prob_new_vehicle_westbound=                0.15;
  double proportion_of_cars=                        0.6;
  double proportion_of_SUVs=                        0.3;
  double proportion_of_trucks = 1-(proportion_of_cars+proportion_of_SUVs);
  double proportion_right_turn_cars=                0.4;
  double proportion_left_turn_cars=                 0.1;
  double proportion_right_turn_SUVs=                0.3;
  double proportion_left_turn_SUVs=                 0.05;
  double proportion_right_turn_trucks=              0.2;
  double proportion_left_turn_trucks=               0.02;


  Animator anim(number_of_sections_before_intersection);

  // This is the current time
  cout <<"its timeStamp"<< endl;
  int timeStamp = 0;

  //Light initialization and set up
  Light* northLight = new Light(green_north_south, yellow_north_south, red_north_south, Color::green, LightDirection::ns);
  Light* southLight = new Light(*northLight);

  Light* eastLight = new Light(green_east_west, yellow_east_west, red_east_west, Color::red, LightDirection::we);
  Light* westLight = new Light(*eastLight);

  //Set up roads
  Roadway* crossway = new Roadway(northLight, eastLight, number_of_sections_before_intersection);

  mt19937 randomNumberGenerator; // Mersenne twister
  uniform_real_distribution<double> rand_double(0,1);

  //randomNumberGenerator.seed(39);
  randomNumberGenerator.seed(initialSeed);

  //loop
  cout << "maximum_simulated_time is"<<maximum_simulated_time<< endl;
  char dummy;
  while (timeStamp<maximum_simulated_time){

    northLight->updateColor(timeStamp);
    southLight->updateColor(timeStamp);
    eastLight->updateColor(timeStamp);
    westLight->updateColor(timeStamp);

    double newVehicle = rand_double(randomNumberGenerator);
    double right = rand_double(randomNumberGenerator);
    double newDirection = rand_double(randomNumberGenerator);

    int totalLength = (number_of_sections_before_intersection * 2)+2;

    //initalize right turn for each vehicle
    bool turnRightCar = false;
    bool turnRightSUV = false;
    bool turnRightTruck = false;
    if (right >= 0 && right<proportion_right_turn_cars){
      turnRightCar = true;
    }
    if (right >= 0 && right<proportion_right_turn_SUVs){
      turnRightSUV = true;
    }
    if (right >= 0 && right<proportion_right_turn_trucks){
      turnRightTruck = true;
    }

    Vehicle v;
    if (newDirection >= 0 && newDirection < prob_new_vehicle_northbound){
      if (newVehicle >= 0 && newVehicle < proportion_of_cars){
        v = Vehicle(VehicleType::car, Direction::north, number_of_sections_before_intersection+2, 1, number_of_sections_before_intersection+2, 0, turnRightCar);
      }
      else if(newVehicle > proportion_of_cars && newVehicle < proportion_of_cars+ proportion_of_SUVs){
        v = Vehicle(VehicleType::suv, Direction::north, number_of_sections_before_intersection+2,2,number_of_sections_before_intersection+2,0,turnRightSUV);
      }
      else if(newVehicle >proportion_of_cars+proportion_of_SUVs && newVehicle < proportion_of_cars+proportion_of_SUVs+proportion_of_trucks){
        v = Vehicle(VehicleType::truck, Direction::north, number_of_sections_before_intersection+2,3,number_of_sections_before_intersection+2,0,turnRightTruck);
      }
      crossway->northbound->addVehicle(new Vehicle(v));
    }

    else if(newDirection >= prob_new_vehicle_northbound && newDirection < prob_new_vehicle_northbound + prob_new_vehicle_southbound){
      if (newVehicle >= 0 && newVehicle<proportion_of_cars){
        v = Vehicle(VehicleType::car, Direction::south, number_of_sections_before_intersection+1, totalLength-2, number_of_sections_before_intersection+1, totalLength-1, turnRightCar);
      }
      else if(newVehicle > proportion_of_cars && newVehicle < proportion_of_cars+ proportion_of_SUVs){
        v = Vehicle(VehicleType::suv, Direction::south, number_of_sections_before_intersection+1, totalLength-3, number_of_sections_before_intersection+1, totalLength-1, turnRightSUV);
      }
      else if(newVehicle >=proportion_of_cars+proportion_of_SUVs && newVehicle < proportion_of_cars+proportion_of_SUVs+proportion_of_trucks){
        v = Vehicle(VehicleType::truck, Direction::south, number_of_sections_before_intersection+1, totalLength-4, number_of_sections_before_intersection+1, totalLength-1, turnRightTruck);
      }
      crossway->southbound->addVehicle(new Vehicle(v));
    }
    else if(newDirection >= prob_new_vehicle_southbound + prob_new_vehicle_northbound && newDirection < prob_new_vehicle_eastbound + prob_new_vehicle_northbound + prob_new_vehicle_southbound){
      if(newVehicle >= 0 && newVehicle < proportion_of_cars){
        v = Vehicle(VehicleType::car, Direction::east,1, number_of_sections_before_intersection, 0, number_of_sections_before_intersection, turnRightCar);
      }
      else if(newVehicle > proportion_of_cars && newVehicle < proportion_of_SUVs + proportion_of_cars){
        v = Vehicle(VehicleType::suv, Direction::east, 2, number_of_sections_before_intersection, 0, number_of_sections_before_intersection, turnRightSUV);
      }
      else if(newVehicle >=proportion_of_cars+proportion_of_SUVs && newVehicle < proportion_of_cars+proportion_of_SUVs+proportion_of_trucks){
        v = Vehicle(VehicleType::truck, Direction::east, 3,number_of_sections_before_intersection, 0, number_of_sections_before_intersection, turnRightTruck);
      }
      crossway->eastbound->addVehicle(new Vehicle(v));
    }
    else if(newDirection >= prob_new_vehicle_eastbound + prob_new_vehicle_northbound + prob_new_vehicle_southbound && newDirection < prob_new_vehicle_westbound + prob_new_vehicle_northbound
  + prob_new_vehicle_southbound + prob_new_vehicle_eastbound){
     if(newVehicle >= 0 && newVehicle < proportion_of_cars){
          v = Vehicle(VehicleType::car, Direction::west,totalLength-2, number_of_sections_before_intersection+1, totalLength-1, number_of_sections_before_intersection+1, turnRightCar);
        }
        else if(newVehicle > proportion_of_cars && newVehicle < proportion_of_SUVs + proportion_of_cars){
          v = Vehicle(VehicleType::suv, Direction::west, totalLength-3, number_of_sections_before_intersection+1, totalLength-1, number_of_sections_before_intersection+1, turnRightSUV);
        }
        else if(newVehicle >=proportion_of_cars+proportion_of_SUVs && newVehicle < proportion_of_cars+proportion_of_SUVs+proportion_of_trucks){
          v = Vehicle(VehicleType::truck, Direction::west, totalLength-4,number_of_sections_before_intersection+1, totalLength-1, number_of_sections_before_intersection+1, turnRightTruck);
        }
        crossway->westbound->addVehicle(new Vehicle(v));
    }
    for (int i =0; i<crossway->northbound->road.size();i++){
      if (crossway->northbound->canAdvance(crossway->northbound->road[i], i, timeStamp, yellow_north_south)){
        if(crossway->isIntersection(crossway->northbound->road[i])){
          if (crossway->northbound->road[i]->turnOr() == true){
            Vehicle* v = crossway->northbound->road[i];
            crossway->northbound->removeVehicle(i);

            v->turnRight();

            crossway->eastbound->insertTurn(v);
          }
          else{
            crossway->northbound->road[i]->advance();
          }
        }

        else{
          crossway->northbound->road[i]->advance();
          }
        }
      }
  crossway->northbound->removeVehicle();

  for(int i=0; i< crossway->southbound->road.size();i++){
    if (crossway->southbound->canAdvance(crossway->southbound->road[i],i,timeStamp,yellow_north_south)){
      if (crossway->isIntersection(crossway->southbound->road[i])){
        if(crossway->southbound->road[i]->turnOr() == true){
          Vehicle* v = crossway->southbound->road[i];
          crossway->southbound->removeVehicle(i);
          v->turnRight();
          crossway->westbound->insertTurn(v);
        }
        else{
          crossway->southbound->road[i]->advance();
        }
      }
      else{
        crossway->southbound->road[i]->advance();
      }
    }
  }
    crossway->southbound->removeVehicle();

  for(int i = 0; i < crossway->eastbound->road.size(); i++){
    if(crossway->eastbound->canAdvance(crossway->eastbound->road[i],i,timeStamp,yellow_east_west)){
      if(crossway->isIntersection(crossway->eastbound->road[i])){
        if(crossway->eastbound->road[i]->turnOr() == true){
          Vehicle* v = crossway->eastbound->road[i];
          crossway->eastbound->removeVehicle(i);
          v->turnRight();
          crossway->southbound->insertTurn(v);
        }
        else{
          crossway->eastbound->road[i]->advance();
        }
      }
      else{
        crossway->eastbound->road[i]->advance();
      }
    }
  }
  	crossway->eastbound->removeVehicle();

    for(int i = 0; i < crossway->westbound->road.size(); i++){
      if(crossway->westbound->canAdvance(crossway->westbound->road[i],i,timeStamp,yellow_east_west)){
        if(crossway->isIntersection(crossway->westbound->road[i])){
          if(crossway->westbound->road[i]->turnOr() == true){
            Vehicle* v = crossway->westbound->road[i];
            crossway->westbound->removeVehicle(i);
            v->turnRight();
            crossway->northbound->insertTurn(v);
          }
          else{
            crossway->westbound->road[i]->advance();
          }
        }
        else{
          crossway->westbound->road[i]->advance();
        }
      }
    }
    	crossway->westbound->removeVehicle();






//For Animator
  vector<VehicleBase*> nouthPtr = crossway -> northbound -> forAnimator();
  vector<VehicleBase*> southPtr = crossway -> southbound -> forAnimator();
  vector<VehicleBase*> eastPtr = crossway -> eastbound -> forAnimator();
  vector<VehicleBase*> westPtr = crossway -> westbound -> forAnimator();
  anim.setVehiclesNorthbound(nouthPtr);
  anim.setVehiclesSouthbound(southPtr);
  anim.setVehiclesEastbound(eastPtr);
  anim.setVehiclesWestbound(westPtr);

  switch(northLight->getColor()){
    case Color::green:
      anim.setLightNorthSouth(LightColor::green);
      break;
    case Color::yellow:
        anim.setLightNorthSouth(LightColor::yellow);
        break;
    case Color::red:
        anim.setLightNorthSouth(LightColor::red);
        break;
  }
  switch(eastLight->getColor()){
    case Color::green:
      anim.setLightEastWest(LightColor::green);
      break;
    case Color::yellow:
        anim.setLightEastWest(LightColor::yellow);
        break;
    case Color::red:
        anim.setLightEastWest(LightColor::red);
        break;
  }

    anim.draw(timeStamp);
    cin.get(dummy);

    timeStamp++;


      }
    }
    return 0;

}
