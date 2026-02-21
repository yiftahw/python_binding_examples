// pose_module.cpp
#include <concepts>
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

// templated function that automatically adds buffer protocol support (as raw byte buffers)
// to any PoD like struct
template <typename T, typename... CtorArgs>
    requires std::is_trivially_copyable_v<T> && std::is_standard_layout_v<T>
py::class_<T> bind_buffer(py::module_ &m, const char *name)
{
    return py::class_<T>(m, name, py::buffer_protocol())
        .def(py::init<CtorArgs...>())
        .def_buffer([](T &self) -> py::buffer_info
                    { return py::buffer_info(
                        // expose as a raw byte buffer
                        reinterpret_cast<uint8_t *>(&self),       // Pointer to buffer
                        1,                                        // size of element in buffer (1 byte for uint8_t)
                        py::format_descriptor<uint8_t>::format(), // Python struct-style format descriptor
                        1,                                        // number of dimensions
                        {sizeof(T)},                              // buffer dimensions
                        {1}                                       // strides (in bytes) for each index
                      ); });
}

PYBIND11_MODULE(pose_module, m) {
    // bind_buffer replaces the usual py::class_ definition
    // to automatically add buffer protocol support for trivially copyable types
    // as raw byte buffers.
    // types defined with `bind_buffer` can be directly read/written using the buffer protocol
    // with (userspace) zero-copy semantics to socket API for example,
    // which is useful for IPC on the same machine.

    bind_buffer<Pose>(m, "Pose")
        .def("set_values", &Pose::set_values, "Set x, y, z coordinates")
        .def_property("x", &Pose::get_x, &Pose::set_x, "X coordinate of the pose")
        .def_property("y", &Pose::get_y, &Pose::set_y, "Y coordinate of the pose")
        .def_property("z", &Pose::get_z, &Pose::set_z, "Z coordinate of the pose")
        .def("__repr__", &Pose::to_string);

    bind_buffer<Line, const Pose&, const Pose&>(m, "Line")
        .def("get_start", &get_start, py::return_value_policy::reference_internal, "Get start Pose of the line")
        .def("get_end", &get_end, py::return_value_policy::reference_internal, "Get end Pose of the line")
        .def("__repr__", &Line::to_string);
}
