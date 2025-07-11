cmake_minimum_required( VERSION 3.16 )
project( LimitlessPotential )

set( CMAKE_CXX_STANDARD 17 )

add_subdirectory( src/json )

#include_directories( src/metamod-p )

add_executable( LimitlessPotential
    src/CConfigContext.cpp
    src/CConfigContext.hpp
    src/main.cpp
    src/placeholder.h
    src/CBasePlugin.h

    src/plugins/anticlip.cpp
)

target_link_libraries( LimitlessPotential nlohmann_json::nlohmann_json )
