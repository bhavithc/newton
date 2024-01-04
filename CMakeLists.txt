cmake_minimum_required(VERSION 3.0.0)
project(newton VERSION 1.0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(COMPANY "Vishal ahirwar")
string(TIMESTAMP CURRENT_YEAR "%Y")
set(COPYRIGHT "Copyright(c) ${CURRENT_YEAR} Vishal Ahirwar. All rights reserved.")

configure_file(newtonConfig.h.in newtonConfig.h)

add_compile_options("-std=c++20")

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_compile_options("-g3")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    add_compile_options("-o3")
endif()

add_executable(${PROJECT_NAME} 
    src/main.cc
    src/source/app.cc
    src/source/newton.cc)

target_include_directories(${PROJECT_NAME} PUBLIC 
    src/includes
    ${PROJECT_BINARY_DIR})

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

