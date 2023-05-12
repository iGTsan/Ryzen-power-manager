cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_COMPILER "/usr/bin/g++")

project(ryzen-power-manager VERSION 1.0 LANGUAGES CXX)



add_compile_options(
    -Werror

    -Wall
    -Wextra
    -Wpedantic

    -Wcast-align
    -Wcast-qual
    -Wconversion
    -Wctor-dtor-privacy
    -Wenum-compare
    -Wfloat-equal
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Woverloaded-virtual
    -Wredundant-decls
    -Wsign-conversion
    -Wsign-promo
)

if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

set(SRC_DIR src)

set(EXECUTABLE ryzen_manager)
set(LIBRARY ryzen_manager_lib)
set(LIBRARY_PATH lib)
set(UI ui)
# set(SOURCE ui/src/main.cpp)
file(GLOB SOURCES ui/src/*.cpp)

include_directories(${LIBRARY_PATH}/headers/)
include_directories(${UI}/headers/)

# set(SOURCES main.cpp)

# file(GLOB SOURCES ${SRC_DIR}/*.cpp)

message("dir " ${CMAKE_CURRENT_SOURCE_DIR})

message("dir " ${CMAKE_CURRENT_LIST_DIR})

message("SOURCES:" ${SOURCES})

add_executable(${EXECUTABLE} ${SOURCES})

add_subdirectory(${LIBRARY_PATH})
enable_testing()
# if (BUILD_TESTING) 
    add_subdirectory(test)
# endif()
# add_subdirectory(ui)

target_link_libraries(${EXECUTABLE} ${LIBRARY})
# target_link_libraries(${EXECUTABLE} ${UI_LIBRARY})