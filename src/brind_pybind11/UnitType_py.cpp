#include "UnitType.h"


#include <stdio.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(MicroRTSpy, m) {
    py::class_<UnitType>(m, "UnitType")
        .def("getName", &UnitType::getName)
        .def("equals", &UnitType::equals)
        .def("produces", &UnitType::produces);
        
       
}
