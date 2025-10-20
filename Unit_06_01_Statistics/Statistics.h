#pragma once
#include <vector>
#include <stdexcept>  // for exceptions


//Function template
//returns the smallest value by comparing the first value in the vector to the next values and assing
//whatever value is smallest to the variable min and return it.
template <typename T>
T getMin(const std::vector<T>& values) {
    if (values.empty()) {
        throw std::runtime_error("Empty vector");
    }
    T min = values[0];
    for (const auto& val : values) {
        if (val < min) min = val;
    }
    return min;
}
////returns the biggest value by comparing the first value in the vector to the next values and assing
//whatever value is biggest to the variable max and return it.
template <typename T>
T getMax(const std::vector<T>& values) {
    if (values.empty()) {
        throw std::runtime_error("Empty vector");
    }
    T max = values[0];
    for (const auto& val : values) {
        if (val > max) max = val;
    }
    return max;
}
//calculates the average by adding all the values in the vector and dividing that value by the size of the vector.
template <typename T>
double getAverage(const std::vector<T>& values) {
    if (values.empty()) {
        throw std::runtime_error("Empty vector");
    }
    double sum = 0.0;
    for (const auto& val : values) {
        sum += val;
    }
    return sum / values.size();
}



//class template
template <typename T>
class Statistics {
private:
    std::vector<T> data;

public:
    void addValue(const T& value) {
        data.push_back(value);
    }
    //uses the function to find the smallest value in order to return the min values in the vector
    T getMin() const {
        return ::getMin(data);  
    }
    //uses the function to find the biggest value in order to return the max values in the vector
    T getMax() const {
        return ::getMax(data);
    }
    //uses the function to find the average in order to return the average in the vector
    double getAverage() const {
        return ::getAverage(data);
    }
};