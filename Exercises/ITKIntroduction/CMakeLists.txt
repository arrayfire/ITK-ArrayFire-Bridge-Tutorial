cmake_minimum_required(VERSION 2.4)
if(COMMAND CMAKE_POLICY)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND CMAKE_POLICY)

project(MedianFilterITK)

find_package(ITK REQUIRED)
if(ITK_FOUND)
  include(${ITK_USE_FILE})
endif()

add_executable(MedianFilterITK MedianFilterITK.cxx )
target_link_libraries(MedianFilterITK ${ITK_LIBRARIES})
