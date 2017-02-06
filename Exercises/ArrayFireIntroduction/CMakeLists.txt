project(MedianFilterArrayFire)

find_package(ArrayFire REQUIRED)

include_directories(${ArrayFire_INCLUDE_DIRS})

add_executable(MedianFilterAF MedianFilterAF.cxx)
target_link_libraries(MedianFilterAF ${ArrayFire_LIBRARIES})
