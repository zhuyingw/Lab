1. Design:
We created Light.h, Road.h, Vehicle.h along with their .cpp files. We also made random.cpp, which keeps track of the randomly generated measures, and Simulation.cpp to tie all the files together and carry out the traffic intersection simulation.

a. Light.h:
Light.h is to set up the traffic light system with utilities such as light-time duration, the cycle of traffic lights, and current-time light color.

b. Road.h:
Road.h is to control the vehicles coming into the streets and disappearing. If a vehicle comes to an end of the road, it gets removed. If there is enough space for a vehicle to come in the road, the vehicle is added.
Road.h also sets up the rules for if a vehicle can turn or advance.

c. Vehicle.h:
Vehicle class inherits from VehicleBase class. Vehicle class specifies the vehicles' features such as sizes, their original direction, and whether they can turn right or not.

d. random.cpp:
We have a separate file to keep track of the feature of the randomly generated number. In this file, we specify at which rate, a vehicle type will appear, and reset the seed each time. The random feature will be used in Simulation.cpp.

e. Simulation.cpp:
This file reads the input and process it to carry out the traffic intersection simulation. It uses VehicleBase class to create the direction and new vehicles coming into the road. It uses the Animator class to set up the traffic lights.


2. How to compile:
Compile the Simulation.cpp file.
