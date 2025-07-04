#pragma once

#include <string>

class Pose {
public:
    Pose() : x(0), y(0) {}

    /// this is a function description  
    // returns void  
    // param x some x value  
    // param y some y value  
    void set_values(float x, float y) {
        this->x = x; 
        this->y = y; 
    }

    // returns a tuple of the values x,y
    std::tuple<float, float> get_values() const {
        return std::make_tuple(x, y);
    }

    std::string to_string() const {
        return "Pose(" + std::to_string(x) + ", " + 
                         std::to_string(y) + ")";
    }

private:
    float x, y;
};
