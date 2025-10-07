// SPDX-FileCopyrightText: Copyright © 2025 ENEA
//
// SPDX-License-Identifier: MPL-2.0

#include <cmath>
#include "fng.hpp"
#include "openmc_sampled/fng_source.hpp"


Particle fng_sample(const std::function<double()>& prng) {
    // Create particle
    Particle p;

    // Setup particle position data structure
    p.rx = 0.;
    p.ry = 0.001;
    p.rz = 0.;

    // Setup particle direction data structures
    double theta = 0;
    int index = 0;
    double scaledR = 0;
    double interplTheta = 0;
    double a = 0;
    double b = 0;

    // Sample direction
    double rnd = prng();

    // check which theta will be used depending on the distribution
    for(int i = 1; i < 40; i++) {
      if(rnd <= angleDistribution[i][1] && rnd > angleDistribution[i-1][1]) {
        a = angleDistribution[i-1][1];
        b = angleDistribution[i][1];
        scaledR = (rnd -  a) / (b - a);
        interplTheta = angleDistribution[i-1][0] + scaledR * (angleDistribution[i][0] - angleDistribution[i-1][0]);
        theta = std::acos(interplTheta);
        index = i;
        break;
      }
    }

    double phi = prng() * 2. * M_PI;

    p.ux = std::sin(theta) * std::cos(phi);
    p.uy = std::cos(theta);
    p.uz = std::sin(theta) * std::sin(phi);

    // putting your position and direction so that program can use it - pointers in C - x,y,z on cylinder
    double angle = prng() * 2. * M_PI;
    double r = 0.7 * std::sqrt(prng());
    p.rx += r * std::cos(angle);
    p.ry += prng() * 0.001;
    p.rz += r * std::sin(angle);

    // Here you need to define the energy of particle depending on the sampled direction
    // new randon number for energy distribution
    rnd = prng();
    for(int i = 1; i < 127; i++) {
      if(rnd <= energyDistibution[i][index] && rnd > energyDistibution[i-1][index]) {
        // energy between the lower and upper value sampled randomly
        p.E = 1.e6 * prng() * (energyDistibution[i][0] - energyDistibution[i-1][0]) + energyDistibution[i-1][0] * 1.e6;
        break;
      }
    }

    return p;
}
