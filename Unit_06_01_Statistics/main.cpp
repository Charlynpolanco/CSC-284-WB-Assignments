#include <iostream>
#include "Statistics.h"

int main() {
    try {
        //object creation
        Statistics<int> intStats;
        intStats.addValue(10);
        intStats.addValue(20);
        intStats.addValue(30);

        Statistics<double> doubleStats;
        doubleStats.addValue(3.14);
        doubleStats.addValue(2.71);
        doubleStats.addValue(4.5);

        Statistics<float> floatStats;
        floatStats.addValue(41.5236f);
        floatStats.addValue(20.542f);
        floatStats.addValue(5.98f);

        // class usage example
        //int

        std::cout << "Int Stats: Min = " << intStats.getMin();
        std::cout << ", Max = " << intStats.getMax()
            << ", Avg = " << intStats.getAverage() << "\n";
        //double
        std::cout << "Double Stats: Min = " << doubleStats.getMin()
            << ", Max = " << doubleStats.getMax()
            << ", Avg = " << doubleStats.getAverage() << "\n";
        //float
        std::cout << "Int Stats: Min = " << floatStats.getMin()
            << ", Max = " << floatStats.getMax()
            << ", Avg = " << floatStats.getAverage() << "\n";

        //direct usage example
        // int
        std::vector<int> intValues = { 10, 20, 30 };
        std::cout << "Using function templates: Min = " << getMin(intValues)
            << ", Max = " << getMax(intValues)
            << ", Avg = " << getAverage(intValues) << "\n";
        //double
        std::vector<double> doubleValues = { 3.14, 2.71, 4.5 };
        std::cout << "Using function templates: Min = " << getMin(doubleValues)
            << ", Max = " << getMax(doubleValues)
            << ", Avg = " << getAverage(doubleValues) << "\n";
        //float
        std::vector<float> floatValues = { 41.5236, 20.542, 5.98 };
        std::cout << "Using function templates: Min = " << getMin(floatValues)
            << ", Max = " << getMax(floatValues)
            << ", Avg = " << getAverage(floatValues) << "\n";
    }
    //catches exceptions prints out an error message.
    catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
    catch (...) {
        std::cerr << "Unknown error has occured.\n";
    }
   
    return 0;
}