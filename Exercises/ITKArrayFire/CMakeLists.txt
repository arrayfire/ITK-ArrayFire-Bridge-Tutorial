cmake_minimum_required(VERSION 2.4)
if(COMMAND CMAKE_POLICY)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND CMAKE_POLICY)

project(ITKArrayFire)

find_package(ITK REQUIRED)
if(ITK_FOUND)
  include(${ITK_USE_FILE})
endif()

find_package(ArrayFire REQUIRED)

add_executable(MedianFilterAFITK MedianFilterAFITK.cxx )
target_link_libraries(MedianFilterAFITK ${ITK_LIBRARIES} ${ArrayFire_LIBRARIES})
