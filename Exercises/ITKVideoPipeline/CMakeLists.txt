find_package(ITK REQUIRED)
if(ITK_FOUND)
  include(${ITK_USE_FILE})
endif()

Find_package(OpenCV REQUIRED)
If(OpenCV_FOUND)
  include_directories(${OpenCV_INCLUDE_DIRS})
Endif()

add_executable(MedianFilterOnVideoITK MedianFilterOnVideoITK.cxx)
target_link_libraries(MedianFilterOnVideoITK ${ITK_LIBRARIES} ${OpenCV_LIBS})
