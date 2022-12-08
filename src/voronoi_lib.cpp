#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include "voronoi.hpp"
#include "point.hpp"

namespace py = pybind11;

PYBIND11_MODULE(Voronoi, m) {
    m.doc() = "compute the voronoi diagram of a set of 2D-points with the fortune algorithm";

    py::class_<Point>(m, "Point")
        .def(py::init<size_t, size_t>(), "2D point")
        .def_property("x", &Point::x, &Point::x)
        .def_property("y", &Point::y, &Point::y);


    /*py::class_<Voronoi>(m, "VoronoiDiagram")
        .def(py::init<size_t, size_t>())
        .def("__setitem__", [](Matrix &self, std::pair<size_t, size_t> index, double val) { self(index.first, index.second) = val; })
        .def("__getitem__", [](Matrix &self, std::pair<size_t, size_t> index) { return self(index.first, index.second); })
        .def("__eq__", &operator==)
        .def_property("nrow", &Matrix::nrow, nullptr)
        .def_property("ncol", &Matrix::ncol, nullptr); /*
}