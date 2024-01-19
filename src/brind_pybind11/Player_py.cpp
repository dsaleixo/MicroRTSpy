#include "Player.h"
#include <stdio.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(MicroRTSpy, m) {
    py::class_<Player>(m, "Player")
        .def(py::init<int,int>())
        .def("getID", &Player::getID)
        .def("getResources", &Player::getResources)
        .def("setResources", Player::setResources)
        .def("toString", Player::toString)
        .def("fromXML", Player::fromXML)
        .def("clone", Player::clone);
       
}

