#pragma once

#include <string>

class Pose {
public:
    Pose() : x(0), y(0), z(0) {}

    /// this is a function description  
    // returns void  
    // param x some x value  
    // param y some y value  
    // param z some z value  
    void set_values(float x, float y, float z) {
        this->x = x; 
        this->y = y; 
        this->z = z;
    }

    std::string to_string() const {
        return "Pose(" + std::to_string(x) + ", " + 
                         std::to_string(y) + ", " +
                         std::to_string(z) + ")";
    }

private:
    float x, y, z;
};
