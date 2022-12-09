#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include "voronoi.hpp"
#include "point.hpp"

namespace py = pybind11;

PYBIND11_MODULE(voronoi_lib, m) {
    m.doc() = "compute the voronoi diagram of a set of 2D-points with the fortune algorithm";

    py::class_<Point>(m, "Point")
        .def(py::init<size_t, size_t, size_t>(), "2D point")
        .def("x", [](Point& p) { return p.x(); })
        .def("x", [](Point& p, double d) { p.x() = d; });
    }