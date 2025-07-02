// pose_module.cpp
#include <boost/python.hpp>
#include <string>

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

BOOST_PYTHON_MODULE(libpose_module)
{
    using namespace boost::python;

    class_<Pose>("Pose")
        .def("set_values", &Pose::set_values)
        .def("__repr__", &Pose::to_string);
}
