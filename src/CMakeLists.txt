# SPDX-FileCopyrightText: Copyright © 2025 ENEA
#
# SPDX-License-Identifier: MPL-2.0

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find dependencies
find_package(nlohmann_json REQUIRED)
find_package(argparse REQUIRED)
set(PYBIND11_FINDPYTHON ON)
find_package(pybind11 CONFIG REQUIRED)

# define executable
add_executable(fngsrc
    main.cpp
    prng_uniform.cpp
    fng.cpp
)

# include and link dependencies
target_include_directories(fngsrc PRIVATE
    ${nlohmann_json_INCLUDE_DIRS}
    ${argparse_INCLUDE_DIRS}
)
target_link_libraries(fngsrc PRIVATE
    nlohmann_json::nlohmann_json
    argparse::argparse
)

# define Python module
pybind11_add_module(pyfngsrc
    fng_bindings.cpp
    prng_uniform.cpp
    fng.cpp
)

# install executable
install(TARGETS fngsrc
    DESTINATION bin
)
# install Python bindings
install(TARGETS pyfngsrc
    DESTINATION lib
)
