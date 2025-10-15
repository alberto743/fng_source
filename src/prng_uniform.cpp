// SPDX-FileCopyrightText: Copyright © 2025 ENEA
//
// SPDX-License-Identifier: MPL-2.0

#include <chrono>
#include <random>

double prng_uniform()
{
    static unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::default_random_engine prn_generator(seed);
    static std::uniform_real_distribution<double> prn_distribution(0.0, 1.0);

    return prn_distribution(prn_generator);
};
