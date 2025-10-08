// SPDX-FileCopyrightText: Copyright © 2025 ENEA
//
// SPDX-License-Identifier: MPL-2.0

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include "prng_uniform.hpp"
#include "fng.hpp"

namespace py = pybind11;

PYBIND11_MODULE(pyfngsrc, m) {
    m.doc() = "FNG source sampler";

    m.def("prng_uniform",
        &prng_uniform,
        "Uniform pseudo-random number generator"
    );

    m.def("sample",
        &fng_sample,
        "Generate particle",
        py::arg("prng")
    );

    //py::class_<Particle, std::shared_ptr<Particle>>(m, "Particle");

    py::class_<Particle>(m, "Particle")
        .def(py::init<const double, const double, const double,
                      const double, const double, const double,
                      const double>(),
                      py::arg("rx"), py::arg("ry"), py::arg("rz"),
                      py::arg("ux"), py::arg("uy"), py::arg("uz"),
                      py::arg("E")
                    )
        .def_readonly("rx", &Particle::rx)
        .def_readonly("ry", &Particle::ry)
        .def_readonly("rz", &Particle::rz)
        .def_readonly("ux", &Particle::ux)
        .def_readonly("uy", &Particle::uy)
        .def_readonly("uz", &Particle::uz)
        .def_readonly("E", &Particle::E)
        .def("__repr__", [](const Particle &p) {
            return "<Particle rx=" + std::to_string(p.rx) +
                   " ry=" + std::to_string(p.ry) +
                   " rz=" + std::to_string(p.rz) +
                   " ux=" + std::to_string(p.ux) +
                   " uy=" + std::to_string(p.uy) +
                   " uz=" + std::to_string(p.uz) +
                   " E=" + std::to_string(p.E) + ">";
        })
        ;
}
