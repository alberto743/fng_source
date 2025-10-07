# SPDX-FileCopyrightText: Copyright © 2025 ENEA
#
# SPDX-License-Identifier: MPL-2.0

cmake_minimum_required(VERSION 3.14)
project(fng_source_sampler LANGUAGES CXX)

find_package(nlohmann_json 3.11.3 REQUIRED)
find_package(argparse 3.2.0 REQUIRED)


target_link_libraries(fng_source_sampler PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(fng_source_sampler PRIVATE argparse)

add_executable(fng_source_sampler example.cpp)
