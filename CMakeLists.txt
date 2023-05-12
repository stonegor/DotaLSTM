cmake_minimum_required(VERSION 3.23)

set(project "dumb-nickname-generator")

project(${project})
find_package(Torch REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

set(CMAKE_CXX_STANDARD 17)

set(${project}_HEADERS
        model/model.h)


set(${project}_SOURCES
        main.cpp
        model/model.cpp
        model/train.cpp)

set(${project}_SOURCE_LIST
        ${${project}_SOURCES})

add_executable(${project}
        ${${project}_SOURCE_LIST})


target_link_libraries(${project} "${TORCH_LIBRARIES}")