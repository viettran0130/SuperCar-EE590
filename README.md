# SuperCar-EE590
This is final project for EE590: Advanced Programming for Embedded Systems.
Using Event Loop Manager called elma to improve and extend functionalities  car.
These following functions will be implemented: 
* Engine: Finite State Machine was implemented to turn on and off the engine
* Gear will contain 4 modes:
    * N = Neutral Mode
    * P = Park Mode
    * D = Drive Mode
    * R = Reverse Mode
 * Break
 * driver simulator
# Run the project
---
    git clone https://github.com/viettran0130/SuperCar-EE590.git
    cd SuperCar-EE590
    docker run -v $PWD:/source -it klavins/elma:latest bash
    make
    cd examples
    bin/driving 
---

# Test Case
* Verify Finite State Machine applied on Engine 
   * random function will define if engine is on/off
* Verify Gear function
   * Engine is off--> velocity = 0
   * Engine is on, Gear sets "D"--> Car is runing , speed increased 
##### Test Status 
* Test Engine on/off (PASSED)
* Test Neutral Mode (PASSED)
* Test Park Mode (PASSED)
* Test Drive Mode (PASSED)
* Test Reverse Mode (PASSED)
* The codes below will demonstrate  
   * Engine off -> velocity = 0 
   * Engine on and Gear set D -> Drive mode -> Speed increasing 
   * Engine on and Gear set P -> Park mode -> velocity = 0

---
void update() {
        int random = rand() % 10;
        if (random % 2==0){
            std::cout << "Engine on" << " \n";
            emit(Event("turn on engine"));
        }else {
            std::cout << "Engine off" <<"    "<< "velocity = 0" << " \n";
            emit(Event("turn off engine"));
            
        }

        json v;
        // v["gear_value"] = "R";
        //  emit(Event("set gear",v));
        // v["gear_value"] = "P";
        //  emit(Event("set gear",v));
        // v["gear_value"] = "N";
        //  emit(Event("set gear",v));
        v["gear_value"] = "D";
         emit(Event("set gear",v));   
    }
---

 
 
 # Engine – Finite State Machine
 * From state off to on -> turn on engine 
 * From state on to off -> turn off engine 
```c++ 
class Engine : public StateMachine {
public:
 
    Engine(std::string name): StateMachine(name), on("on"), off("off")
     {
        add_transition("turn on engine", off, on);
        add_transition("turn off engine", on, off);
        set_initial(off);
    }

private:
    EngineState on;
    EngineState off;
    
};

```
# Automatic Gear 
* Four gear modes has been successfully implemented: P, N, D , R 
```c++
 void update() {
        force=1000
        if (can_run==false){
            velocity = 0;
            return ; 
        }
        if (gear == "N")  {
            std::cout << "Engine on" << " \n";
            std::cout << "Neutral Mode" << " \n";
            velocity = 0;
        }else if (gear == "P"){
            std::cout << "Engine on" << " \n";
            std::cout << "Park Mode" << " \n";
            velocity = 0;
        }else if( gear == "D") {
            std::cout << "Engine on" << " \n";
            std::cout << "Drive Mode" << " \n";
            foward = true;
            velocity += ( delta() / 1000 ) * ( - k * velocity + force ) / m;   
        } else if (gear == "R"){
            std::cout << "Engine on" << " \n";
            std::cout << "Reverse Mode" << " \n";
            foward = false; 
            velocity += -1*(( delta() / 1000 ) * ( - k * velocity + force ) / m);

        }
        channel("Velocity").send(velocity);
        std::cout << "Time=" <<  milli_time() << "  ,  "
                 << "velocity="<<  velocity << " \n";   
 }
```
 
# Break 
* Car is running, break applies -> velocity gradually decreased.  
* Velocity =0 -> Car stops 

# Milestones

##### Week of March 11
* Implement and integrate Gear function 
* Implement and integrate Break function
* Implement and integrate Engine function (apply State machine)

##### Week of March 18 
* Use Doxygen to document 

##### Deadline March 21
* Submit project 












