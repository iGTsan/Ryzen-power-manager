cmake_minimum_required(VERSION 3.13)

project(ryzen-power-manager VERSION 1.0 LANGUAGES CXX)

option(MANAGER_TESTING "Включить модульное тестирование" ON)
option(MANAGER_COVERAGE "Включить измерение покрытия кода тестами" OFF)

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

set(SOURCES ./src/main.cpp)

add_executable(ryzen_maneger ${SOURCES})


