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

    float& get_x() { return x; }
    float& get_y() { return y; }
    float& get_z() { return z; }

    void set_x(float _x) { x = _x; }
    void set_y(float _y) { y = _y; }
    void set_z(float _z) { z = _z; }
private:
    float x, y, z;
};
static_assert(std::is_trivially_copyable_v<Pose>, "Pose must be trivially copyable");

class Line {
public:
    Pose start, end;
    Line(const Pose& start_, const Pose& end_) : start(start_), end(end_) {}
    std::string to_string() const {
        return "Line(" + start.to_string() + ", " + end.to_string() + ")";
    }
};

static_assert(std::is_trivially_copyable_v<Line>, "Line must be trivially copyable");

Pose& get_start(Line& self) { return self.start; }
Pose& get_end(Line& self) { return self.end; }

PYBIND11_MODULE(pose_module, m) {
    py::class_<Pose>(m, "Pose", py::buffer_protocol())
        .def(py::init<>())
        .def("set_values", &Pose::set_values, "Set x, y, z coordinates")
        .def_property("x", &Pose::get_x, &Pose::set_x, "X coordinate of the pose")
        .def_property("y", &Pose::get_y, &Pose::set_y, "Y coordinate of the pose")
        .def_property("z", &Pose::get_z, &Pose::set_z, "Z coordinate of the pose")
        .def("__repr__", &Pose::to_string)
        .def_buffer([](Pose& p) -> py::buffer_info {
            return py::buffer_info(
                // expose as a raw byte buffer
                &p,                               // Pointer to buffer
                1,                                // Size of one scalar (uint8_t)
                py::format_descriptor<uint8_t>::format(), // Python struct-style format descriptor
                1,                                  // Number of dimensions
                { sizeof(Pose) },                  // Buffer dimensions
                { 1 }                               // Strides (in bytes) for each index
            );
        });

    py::class_<Line>(m, "Line", py::buffer_protocol())
        .def(py::init<const Pose&, const Pose&>())
        .def("get_start", &get_start, py::return_value_policy::reference_internal, "Get start Pose of the line")
        .def("get_end", &get_end, py::return_value_policy::reference_internal, "Get end Pose of the line")
        .def("__repr__", &Line::to_string)
        .def_buffer([](Line& l) -> py::buffer_info {
            return py::buffer_info(
                // expose as a raw byte buffer
                &l,                               // Pointer to buffer
                1,                                // Size of one scalar (uint8_t)
                py::format_descriptor<uint8_t>::format(), // Python struct-style format descriptor
                1,                                 // Number of dimensions
                { sizeof(Line) },                  // Buffer dimensions
                { 1 }                              // Strides (in bytes) for each index
            );
        });
        
}
