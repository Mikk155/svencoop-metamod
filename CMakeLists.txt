cmake_minimum_required( VERSION 3.16 )
project( LimitlessPotential )

set( CMAKE_CXX_STANDARD 17 )

add_subdirectory( src/json )
add_subdirectory( src/fmt )

# Maybe i should just fork metamod-p?
if( MSVC )
    add_compile_options( /wd4311 )
    add_compile_options( /wd4005 )
endif()

include_directories(
    ${CMAKE_SOURCE_DIR}/src/metamodp/metamod
    ${CMAKE_SOURCE_DIR}/src/metamodp/hlsdk/common
    ${CMAKE_SOURCE_DIR}/src/metamodp/hlsdk/engine
    ${CMAKE_SOURCE_DIR}/src/metamodp/hlsdk/dlls
    ${CMAKE_SOURCE_DIR}/src/metamodp/hlsdk/pm_shared
)

add_library( ${PROJECT_NAME} SHARED
    src/meta_api.cpp
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

set( DLL_OUTPUT "" CACHE PATH "Binary path")

if( DLL_OUTPUT )
    add_custom_command( TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Installing ${DLL_OUTPUT}/$<TARGET_FILE_NAME:${PROJECT_NAME}>"
        COMMAND ${CMAKE_COMMAND} -E make_directory ${DLL_OUTPUT}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:${PROJECT_NAME}>
        ${DLL_OUTPUT}/$<TARGET_FILE_NAME:${PROJECT_NAME}>
    )
endif()
