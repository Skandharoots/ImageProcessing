cmake_minimum_required(VERSION 3.4)
project(Library)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        include/brightness.h
        include/CImg.h
        include/contrast.h
        include/engine.h
        include/help.h
        include/fliphorizontal.h
        include/flipvertical.h
        include/GeometricMeanFilter.h
            src/brightness.cpp
            src/contrast.cpp
            src/engine.cpp
            src/help.cpp
            src/fliphorizontal.cpp
            src/flipvertical.cpp
            src/GeometricMeanFilter.cpp
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

