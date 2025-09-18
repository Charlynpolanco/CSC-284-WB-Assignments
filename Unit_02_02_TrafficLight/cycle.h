#pragma once
#include <vector>
#include <string>

namespace Lights {

	class TrafficLights
	{
	private:
		int currentLight;
		std::vector<std::string> lights;

	public:
		//constructor
		TrafficLights();
		void cycleChanges(int changes);
	};
}