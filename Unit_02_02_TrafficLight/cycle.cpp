#include "cycle.h"
#include <iostream>


namespace Lights {
	
	TrafficLights::TrafficLights() : currentLight(0), lights({ "Red", "Green", "Yellow" }) {}
	//cycles through the lights the same amount of times as the user says
	void TrafficLights::cycleChanges(int changes) {
        for (int i = 0; i < changes; i++) {
            std::cout << lights[currentLight] << std::endl;
            currentLight++;
            //sets the currentLight to 0 if currentLight reaches 3 to continue the cycle
            if (currentLight == lights.size()) {
                currentLight = 0;
            }
        }
	}

}
