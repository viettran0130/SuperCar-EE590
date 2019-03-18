# SuperCar-EE590
This is final project for EE590: Advanced Programming for Embedded Systems.
Using Event Loop Manager called elma to improve and extend functionalities  car.
These following functions will be implemented: 
* Gear will contain 4 modes:
    N = Neutral Mode
    P = Park Mode
    D = Drive Mode
    R = Reverse Mode
 * Break
 * driver simulator
# Run the project 
    git clone https://github.com/viettran0130/SuperCar-EE590.git
    cd SuperCar-EE590
    docker run -v $PWD:/source -it klavins/elma:latest bash
    make
    examples# bin/driving 
    
# Milestones

##### Week of March 11
* Implement and integrate Gear function
* Implement and integrate Break function
* Implement and integrate Engine function (apply State machine)

##### Week of March 18 
* Implement and integrate Steering wheel 
* Implement and integrate driver simulator 
* Use Doxygen to document 

##### Deadline March 21
* Submit project 

# Current Status 

##### Successfully Developed Gear function
* N = Neutral Mode
* P = Park Mode
* D = Drive Mode
* R = Reverse Mode

##### Successfully Developed Driver Class to test Gear function 
* Test Neutral Mode (PASSED)
* Test Park Mode (PASSED)
* Test Drive Mode (PASSED)
* Test Reverse Mode (PASSED)

Test Example: 
  * Engine off -> velocity = 0 
  * Engine on and Gear set D -> Drive mode -> Speed increasing 
  * Engine on and Gear set P -> Park mode -> velocity = 0 
 
    











