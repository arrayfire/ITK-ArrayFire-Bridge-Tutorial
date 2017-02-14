find_package(ITK REQUIRED)
if(ITK_FOUND)
  include(${ITK_USE_FILE})
endif()

find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
  include_directories(${OpenCV_INCLUDE_DIRS})
endif()

find_package(ArrayFire REQUIRED)
if(ArrayFire_FOUND)
    include_directories(${ArrayFire_INCLUDE_DIRS})
endif()

add_executable(VideoFilteringAFOpenCVBridge VideoFilteringAFOpenCVBridge.cxx)
target_link_libraries(VideoFilteringAFOpenCVBridge
                      ${ITK_LIBRARIES}
                      ${OpenCV_LIBS}
                      ${ArrayFire_LIBRARIES})
