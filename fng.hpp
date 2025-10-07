// SPDX-FileCopyrightText: Copyright © 2025 ENEA
//
// SPDX-License-Identifier: MPL-2.0

#include <functional>

struct Particle
{
    double rx;    // position
    double ry;
    double rz;
    double ux;    // direction
    double uy;
    double uz;
    double E;     // energy
};


Particle fng_sample(const std::function<double()>& prng);
