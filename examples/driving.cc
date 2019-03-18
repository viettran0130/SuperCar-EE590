#include <iostream>
#include <chrono>
#include "elma.h"
#include <stdlib.h> 
// #include "koolplot.h"
// #include <chplot.h>
// #include <chplot.h>

//! \file

using namespace std::chrono;
using std::vector;
using namespace elma;

class Car : public Process {
    public:
    Car(std::string name) : Process(name) {}
    void init() {
       
        // gear 
        watch("set gear", [this](Event& e) {
           json v; 
           v = e.value();
           gear = v["gear_value"].get<std::string>();
          //  std::cout << "set gear" << " \n";
        });

       // Engine 

        watch("engine on", [this](Event& e) {
            can_run =true; 
        });

        watch("engine off", [this](Event& e) {
            can_run =false; 
        });

    }
    void start() {
        velocity = 0;
    }
    void update() {
        // if ( channel("Throttle").nonempty() ) {
            // force = channel("Throttle").latest();
             force=1000;
        // }

        if (can_run==false){
            velocity = 0;
            return ; 
        }
       // std::cout << gear << " \n";
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
        // std::cout << milli_time() << ","
        //           << velocity << " \n";
        std::cout << "Time=" <<  milli_time() << "  ,  "
                 << "velocity="<<  velocity << " \n";
        
        // Plotdata x=milli_time(), y = velocity;
        // plot(x, y);
        
    }
    void stop() {}
    
    private:
    double velocity;
    double force;
    const double k = 0.02;
    const double m = 1000;
    // Gear function//
    string gear = "P"; 
    bool foward = true; 
    // Engine 
    bool can_run = false; 
    // add Break function 


    // add wheel 



    // add simulator 
   
};  


class CruiseControl : public Process {
    public:
    CruiseControl(std::string name) : Process(name) {}
    void init() {
        watch("desired speed", [this](Event& e) {
            desired_speed = e.value();
        });
    }
    void start() {}
    void update() {
        if ( channel("Velocity").nonempty() ) {
            speed = channel("Velocity").latest();
        }
        channel("Throttle").send(-KP*(speed - desired_speed));
    }
    void stop() {}
    private:
    double speed = 0;
    double desired_speed = 0.0;
    const double KP = 314.15;
                 vector<double> _v;
};
// Test Driver function 
class Driver : public Process {

    public: 
    Driver(std::string name) : Process(name) {}
    void init() {
        desired_speed = 50;
    }
    void start() {}
    void update() {
        int random = rand() % 10;
        if (random % 2==0){
            std::cout << "Engine on" << " \n";
            emit(Event("turn on engine"));
        }else {
            std::cout << "Engine off" <<"    "<< "velocity = 0" << " \n";
            emit(Event("turn off engine"));
            
        }
    //    std::cout << "Engine off" << " \n";

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
    void stop() {}
    private:
    double desired_speed;

};




class EngineState : public State {
public:
 
    EngineState(): State() {}
    EngineState(std::string name): State(name) {}

    void entry(const Event& e) {
        if (name()=="on") {
            emit(Event("engine on"));
        } else emit(Event("engine off"));
    }
    void during() {} 
    void exit(const Event& e) {}
};

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
    
   // bool key = true; 

};




int main() {


    

    Manager m;
    
    Car car("Car");
    // CruiseControl cc("Control");
     Driver driver("Steve");
     Channel throttle("Throttle");
     Channel velocity("Velocity");

     Engine engine("Engine");

    m.schedule(car, 100_ms)
    // .schedule(cc, 100_ms)
     .schedule(driver, 5_s)
     .schedule(engine, 5_s)
     .add_channel(throttle)
     .add_channel(velocity)
    
    .init()
    .run(40_s)
    //.start()
    //.emit(Event("set gear", { "gear_value" , "D"}))
    ;


   // m.emit(Event("on button pressed"));

}