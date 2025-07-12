cmake_minimum_required( VERSION 3.16 )
project( LimitlessPotential )

set( CMAKE_CXX_STANDARD 17 )

add_subdirectory( src/json )
add_subdirectory( src/fmt )

include_directories(
    ${CMAKE_SOURCE_DIR}/src/metamodp/hlsdk/common
    ${CMAKE_SOURCE_DIR}/src/metamodp/hlsdk/engine
    ${CMAKE_SOURCE_DIR}/src/metamodp/hlsdk/dlls
    ${CMAKE_SOURCE_DIR}/src/metamodp/hlsdk/pm_shared
)

add_library( ${PROJECT_NAME} SHARED
    src/main.cpp
    src/main.hpp
    src/CBasePlugin.cpp
    src/CConfigContext.cpp
    src/CPluginManager.cpp

    src/plugins/anticlip.cpp
)

target_link_libraries( ${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json )
target_link_libraries( ${PROJECT_NAME} PRIVATE fmt )

# Testing stuff
add_executable( TestPluginLoader test/main.cpp )
