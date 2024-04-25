cmake_minimum_required(VERSION 3.27)
project(mixerdialog)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})

find_package(ALSA REQUIRED)

add_executable(mixerdialog main.cpp
        modules/CssManager.cpp
        modules/CssManager.h
        modules/MixerManager.cpp
        modules/MixerManager.h
)

target_link_libraries(mixerdialog ${GTK3_LIBRARIES})

if (ALSA_FOUND)
    include_directories(${ALSA_INCLUDE_DIRS})
    target_link_libraries(mixerdialog ${ALSA_LIBRARIES})
endif (ALSA_FOUND)

configure_file(${CMAKE_SOURCE_DIR}/style.css ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/images/volume.png ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)