#pragma once

#include <cmath>
#include "pose.hpp"
class Line {
public:
    Line(Pose p1, Pose p2) : p1(p1), p2(p2) {}

    /// Returns the length of the line segment.
    float length() const {
        auto [x1, y1] = p1.get_values();
        auto [x2, y2] = p2.get_values();
        return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
    }

    // @returns slope of the line segment
    // @note might return std::numeric_limits<float>::infinity() if the line is vertical
    float m() const {
        auto [x1, y1] = p1.get_values();
        auto [x2, y2] = p2.get_values();
        if (x2 - x1 == 0) {
            return std::numeric_limits<float>::infinity(); // vertical line
        }
        return (y2 - y1) / (x2 - x1);
    }

    // @returns y-intercept of the line segment
    // @note might return std::numeric_limits<float>::infinity() if the line is vertical
    float n() const {
        auto [x1, y1] = p1.get_values();
        auto [x2, _] = p2.get_values();
        if (x2 - x1 == 0) {
            return std::numeric_limits<float>::infinity(); // vertical line
        }
        return y1 - m() * x1;
    }

    std::string to_string() const {
        return "y = " + std::to_string(m()) + " * x + " + std::to_string(n());
    }

    Pose& get_p1() /* return_value_policy::reference */ {
        return p1;
    }

    Pose& get_p2() {
        return p2;
    }

private:
    Pose p1, p2;
};
