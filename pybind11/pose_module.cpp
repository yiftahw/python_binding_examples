// pose_module.cpp
#include <pybind11/pybind11.h>

namespace py = pybind11;

class Pose {
public:
    Pose() : x(0), y(0), z(0) {}

    void set_values(float x_, float y_, float z_) {
        x = x_; y = y_; z = z_;
    }

    std::string to_string() const {
        return "Pose(" + std::to_string(x) + ", " + 
                         std::to_string(y) + ", " +
                         std::to_string(z) + ")";
    }

private:
    float x, y, z;
};

PYBIND11_MODULE(pose_module, m) {
    py::class_<Pose>(m, "Pose")
        .def(py::init<>())
        .def("set_values", &Pose::set_values, "Set x, y, z coordinates")
        .def("__repr__", &Pose::to_string);
}
