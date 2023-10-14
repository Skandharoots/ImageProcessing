cmake_minimum_required(VERSION 3.4)
project(Library)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        include/Brightness.h
        include/CImg.h
        include/Contrast.h
        include/Engine.h
        include/Help.h
        include/FlipHorizontal.h
        include/FlipVertical.h
        include/GeometricMeanFilter.h
        include/AlphaTrimmedMeanFilter.h
        include/MeanSquareError.h
        include/PeakMeanSquareError.h
            src/Brightness.cpp
            src/Contrast.cpp
            src/Engine.cpp
            src/Help.cpp
            src/FlipHorizontal.cpp
            src/FlipVertical.cpp
            src/GeometricMeanFilter.cpp
            src//AlphaTrimmedMeanFilter.cpp
            src/MeanSquareError.cpp
            src/PeakMeanSquareError.cpp
        )

add_library(Library ${SOURCE_FILES})

#add 'include' directory with header files from 'Library' project to paths
target_include_directories(Library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)



include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)


target_link_libraries (
        Library
        )

