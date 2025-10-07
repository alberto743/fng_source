// SPDX-FileCopyrightText: Copyright © 2025 ENEA
//
// SPDX-License-Identifier: MPL-2.0

#include <functional>

struct Position
{
    double x;
    double y;
    double z;
};


struct Particle
{
    Position r;     // position
    double u[3];    // direction
    double E;       // energy
};


Particle fng_sample(const std::function<double()>& prng);
