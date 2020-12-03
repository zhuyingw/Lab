#include <iostream>
#include "Animator.h"
#include "VehicleBase.h"
#include "Road.h"

int main()
{
    //Animator::MAX_VEHICLE_COUNT = 9999;  // vehicles will be displayed with four digits
    Animator::MAX_VEHICLE_COUNT = 999;  // vehicles will be displayed with three digits
    //Animator::MAX_VEHICLE_COUNT = 99;  // vehicles will be displayed with two digits
    
    // Need to add code to read in inputs

    int halfSize = number_of_sections_before_intersection;  // number of sections before intersection

    Animator anim(halfSize);

    // construct vectors of VehicleBase* of appropriate size, init to nullptr
    std::vector<VehicleBase*> westbound(halfSize * 2 + 2, nullptr);
    std::vector<VehicleBase*> eastbound(halfSize * 2 + 2, nullptr);
    std::vector<VehicleBase*> southbound(halfSize * 2 + 2, nullptr);
    std::vector<VehicleBase*> northbound(halfSize * 2 + 2, nullptr);

    char dummy;
    double random; // put random number generator here
    
    int totalNumVehicles = 0; 

    // CREATE NEW VEHICLE - NORTHBOUND
    if ( random <= prob_new_vehicle_northbound ){ // If true, create new vehicle
        if ( random <= proportion_of_cars ){
        VehicleBase northCar(VehicleType::car, Direction::north); // create car
            totalNumVehicles++;
        }
        else if ( random <= proportion_of_SUVs ){
        VehicleBase northSUV(VehicleType::suv, Direction north); // create suv
            totalNumVehicles++;
        }
        else {
        VehicleBase northTruck(VehicleType::truck, Direction north); // create truck
            totalNumVehicles++;
        }
    }
    
    // CREATE NEW VEHICLE - SOUTHBOUND
    if ( random <= prob_new_vehicle_southbound ){ // If true, create new vehicle
        if ( random <= proportion_of_cars ){
        VehicleBase southCar(VehicleType::car, Direction::south); // create car
            totalNumVehicles++;
        }
        else if ( random <= proportion_of_SUVs ){
        VehicleBase southSUV(VehicleType::suv, Direction::south); // create suv
            totalNumVehicles++;
        }
        else {
        VehicleBase southTruck(VehicleType::truck, Direction::south); // create truck
            totalNumVehicles++;
        }
    }
    
    // CREATE NEW VEHICLE - WESTBOUND
    if ( random <= prob_new_vehicle_westbound ){ // If true, create new vehicle
        if ( random <= proportion_of_cars ){
        VehicleBase westCar(VehicleType::car, Direction::west); // create car
        totalNumVehicles++;
        }
        else if ( random <= proportion_of_SUVs ){
        VehicleBase westSUV(VehicleType::suv, Direction::west); // create suv
        totalNumVehicles++;
        }
        else {
        VehicleBase westTruck(VehicleType::truck, Direction::west); // create truck
        totalNumVehicles++;
        }
    }
    
    // CREATE NEW VEHICLE - EASTBOUND
    if ( random <= prob_new_vehicle_eastbound ){ // If true, create new vehicle
        if ( random <= proportion_of_cars ){
        VehicleBase northCar(VehicleType::car, Direction::east); // create car
        totalNumVehicles++;
        }
        else if ( random <= proportion_of_SUVs ){
        VehicleBase northSUV(VehicleType::suv, Direction::east); // create suv
        totalNumVehicles++;
        }
        else {
        VehicleBase northTruck(VehicleType::truck, Direction::east); // create truck
        totalNumVehicles++;
        }
    }
    
    int duration = 0;
    int i = 0; 

    anim.setLightNorthSouth(LightColor::green);
    anim.setLightEastWest(LightColor::red);
    
    while ( duration < maximum_simulated_time) {
    
        for (; i < green_north_south + yellow_north_south; i++) // Run for length of green + yellow
        {   
            // If space ahead is avaliable, move N/S vehiles by one 
            for ( int j = 0, j < numVehicles; j++){
                if (northbound[j].canAdvance()){
                northbound[i+1] = northbound[i]; // example spot 1 will now hold stuff from spot 0
                }
                if (southbound[j].canAdvance()){
                southbound[i+1] = southbound[i];
                }
            }

            // Make animation show new moves:
            anim.setVehiclesNorthbound(northbound);
            anim.setVehiclesWestbound(westbound);
            anim.setVehiclesSouthbound(southbound);
            anim.setVehiclesEastbound(eastbound);

            anim.draw(i);
            std::cin.get(dummy);

            southbound.assign(halfSize * 2 + 2, nullptr); // reset vector
            northbound.assign(halfSize * 2 + 2, nullptr); // reset
            eastbound.assign(halfSize * 2 + 2, nullptr); // reset
            westbound.assign(halfSize * 2 + 2, nullptr); // reset

        } // When execution gets here, loop has ran for length of green and yellow

        // Now for the east and west to move
        anim.setLightNorthSouth(LightColor::red);
        anim.setLightEastWest(LightColor::green);


            // If end of car is above index length of road, remove vehicle

    int k = 0;

            for (; k < green_east_west + yellow_east_west; k++) // Run for length of green + yellow
        {   
            // If space ahead is avaliable, move W/E vehiles by one 
            for ( int j = 0, j < numVehicles; j++){
                if (westbound[j].canAdvance()){
                westbound[i+1] = westbound[i]; // example spot 1 will now hold stuff from spot 0
                }
                if (eastbound[j].canAdvance()){
                eastbound[i+1] = eastbound[i];
                }
            }

            // Make animation show new moves:
            anim.setVehiclesNorthbound(northbound);
            anim.setVehiclesWestbound(westbound);
            anim.setVehiclesSouthbound(southbound);
            anim.setVehiclesEastbound(eastbound);

            anim.draw(i);
            std::cin.get(dummy);

            southbound.assign(halfSize * 2 + 2, nullptr); // reset vector
            northbound.assign(halfSize * 2 + 2, nullptr); // reset
            eastbound.assign(halfSize * 2 + 2, nullptr); // reset
            westbound.assign(halfSize * 2 + 2, nullptr); // reset

        } // When execution gets here, loop has ran for length of green and yellow

            duration = i + k;  
        
    } // when execution gets here, maximum simulation time is up.
    
}
