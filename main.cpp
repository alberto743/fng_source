// SPDX-FileCopyrightText: Copyright © 2025 ENEA
//
// SPDX-License-Identifier: MPL-2.0

#include <iostream>
#include <functional>
#include <fstream>
#include <argparse/argparse.hpp>
#include <nlohmann/json.hpp>
#include "prng_uniform.hpp"
#include "fng.hpp"


using json = nlohmann::json;


int main(int argc, char* argv[])
{
    // Argument parser
    argparse::ArgumentParser program("FNG source sampler", "0.1");
    program.add_argument("particles")
        .help("Number of particles to be generated")
        .scan<'i', int>();

    program.add_argument("-o", "--output")
        .default_value(std::string("particles.json"))
        .required()
        .help("Output file in JSON format to store the particles generated");

    program.add_argument("--verbose")
        .help("Dump particles to stdout")
        .default_value(false)
        .implicit_value(true);

    try {
        program.parse_args(argc, argv);
    }
    catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        return 1;
    }

    auto samples = program.get<int>("particles");
    auto outname = program.get<std::string>("--output");
    auto explicit_outname = program.is_used("--output");
    auto verbose = program.is_used("--verbose");

    // Initialize JSON output object
    json output_json;
    if (explicit_outname) {
        output_json["particles"] = json::array();
    }

    // Generation of particles
    for(int i=0; i<samples; ++i) {
        Particle p = fng_sample(prng_uniform);

        if (verbose) {
            std::cout << p.rx << " " << p.ry << " " << p.rz << " "
                      << p.ux << " " << p.uy << " " << p.uz << " "
                      << p.E << std::endl;
        }

        if (explicit_outname) {
            json pjson;
            pjson["rx"] = p.rx;
            pjson["ry"] = p.ry;
            pjson["rz"] = p.rz;
            pjson["ux"] = p.ux;
            pjson["uy"] = p.uy;
            pjson["uz"] = p.uz;
            pjson["E"] = p.E;
            output_json["particles"].push_back(pjson);
        }
    }

    // Write output file
    if (explicit_outname) {
        if (verbose) {
            std::string output_json_serialized = output_json.dump();
            std::cout << output_json_serialized << std::endl;
        }

        std::ofstream outfile(outname);
        outfile << std::setw(2) << output_json << std::endl;
    }

    return 0;
}
