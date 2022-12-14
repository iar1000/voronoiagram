#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include "voronoi.hpp"
#include "point.hpp"
#include "fortune.hpp"

namespace py = pybind11;

PYBIND11_MODULE(voronoi_lib, m) {
    m.doc() = "compute the voronoi diagram of a set of 2D-points with the fortune algorithm";

    py::class_<Point>(m, "Point")
        .def(py::init<double, double, size_t>(), "2D point")
        .def("x", [](Point& p) { return p.x(); })
        .def("x", [](Point& p, double d) { p.x() = d; })
        .def("y", [](Point& p) { return p.y(); })
        .def("y", [](Point& p, double d) { p.y() = d; });

    py::class_<Edge>(m, "Edge")
        .def("left_target", [](Edge& e) { return e.leftTarget(); }, pybind11::return_value_policy::reference)
        .def("right_target", [](Edge& e) { return e.rightTarget(); }, pybind11::return_value_policy::reference)
        .def("start_point", [](Edge& e) { return e.startPoint(); }, pybind11::return_value_policy::reference)
        .def("end_point", [](Edge& e) { return e.endPoint(); }, pybind11::return_value_policy::reference);

    py::class_<Voronoi>(m, "Voronoi")
        .def(py::init<std::vector<Point*>>(), "Voronoi Diagram")
        .def("get_target_points", &Voronoi::getTargetPoints)
        .def("get_edges", &Voronoi::getEdges);

    py::class_<FortuneAlgorithm>(m, "Fortune")
        .def(py::init<Voronoi*>(), "Fortune Algorithm")
        .def("compute", &FortuneAlgorithm::compute);

}