# SPDX-FileCopyrightText: Copyright © 2025 ENEA
#
# SPDX-License-Identifier: MPL-2.0

cmake_minimum_required(VERSION 3.16)
project(fng_source_sampler VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
add_executable(fng_source_sampler main.cpp prng_uniform.cpp fng.cpp)

# Find nlohmann_json
find_package(nlohmann_json REQUIRED)

# Find argparse (assumes it's installed as a package)
find_package(argparse REQUIRED)

# Include directories if needed
target_include_directories(fng_source_sampler PRIVATE ${nlohmann_json_INCLUDE_DIRS} ${argparse_INCLUDE_DIRS})

# Link libraries
target_link_libraries(fng_source_sampler PRIVATE nlohmann_json::nlohmann_json argparse::argparse)

# Optionally, install target
install(TARGETS fng_source_sampler DESTINATION bin)
