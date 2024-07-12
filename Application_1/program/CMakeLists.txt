cmake_minimum_required(VERSION 3.4)

project(Program)

#specify set of project's source files
set(SOURCE_FILES
        src/main.cpp
        )
#add following files to executable file 'Program'
add_executable(Program ${SOURCE_FILES})

#add libraries from 'Library' project
target_link_libraries(Program Library)

if(APPLE)
        message(STATUS "Looking for X11...")
        find_package(X11 REQUIRED)
        include_directories(${X11_INCLUDE_DIR})
        target_link_libraries(Program ${X11_LIBRARIES})
endif()

#add header files from 'include' directory of main project
target_include_directories(Program PUBLIC include)

enable_testing()