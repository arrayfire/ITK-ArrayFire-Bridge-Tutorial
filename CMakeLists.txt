cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(ITK-ArrayFire-Bridge)

set(CMAKE_MODULE_PATH ${ITK-ArrayFire-Bridge_SOURCE_DIR}/CMake ${CMAKE_MODULE_PATH})

file(GLOB_RECURSE CXX_FILES "*.cxx")

add_subdirectory(Exercises)
