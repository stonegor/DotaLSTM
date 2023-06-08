cmake_minimum_required(VERSION 3.23)

set(project "dumb-nickname-generator")

project(${project})
find_package(Torch REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH "/opt/Qt5.7.0/5.7/gcc_64/")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/model/model.pt
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/GUI/stylesheet.qss
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

set(${project}_HEADERS
        model/model.h
        GUI/Window.h)


set(${project}_SOURCES
        main.cpp
        model/model.cpp
        model/train.cpp
        GUI/Window.cpp)

set(${project}_SOURCE_LIST
        ${${project}_SOURCES})

add_executable(${project}
        ${${project}_SOURCE_LIST})


target_link_libraries(${project}
        "${TORCH_LIBRARIES}"
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets)

ADD_DEFINITIONS(-DQT_NO_KEYWORDS)

find_package(Qt5Widgets REQUIRED)