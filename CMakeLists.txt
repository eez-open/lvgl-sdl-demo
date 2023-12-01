cmake_minimum_required(VERSION 3.14)

project(lvgl-sdl-demo LANGUAGES C CXX)

find_package(PkgConfig)
pkg_check_modules(SDL2 REQUIRED sdl2)

set(PROJECT_DIR "${CMAKE_SOURCE_DIR}")
set(LVGL_DIR "${PROJECT_DIR}/lvgl")
set(LVDRV_DIR "${PROJECT_DIR}/lvgl_drv")
set(LV_CONF_PATH ${PROJECT_DIR}/lv_conf.h CACHE STRING "" FORCE)
add_definitions(-DLV_LVGL_H_INCLUDE_SIMPLE)
add_definitions(-DLV_CONF_PATH=${LV_CONF_PATH})
add_library(lvglsdl ${LVDRV_DIR}/lv_sdl_disp.c ${LVDRV_DIR}/lv_port_indev.c)
target_include_directories(lvglsdl PUBLIC ${SDL2_INCLUDE_DIRS})

add_definitions(-DEEZ_FOR_LVGL)

include_directories(
    ./eez-framework/src
    ./eez-framework/src/eez/libs/agg
    ./eez-framework/src/eez/platform/simulator
)

file(GLOB_RECURSE eez_framework_src_files
    ./eez-framework/src/eez/*.cpp
    ./eez-framework/src/eez/*.c
)

file(GLOB_RECURSE demo_src_files
    ./src/*.cpp
    ./src/*.c
)

set(SOURCES)
list(APPEND SOURCES ${eez_framework_src_files} ${demo_src_files})

add_executable(lvgl-sdl-demo ${SOURCES})

add_compile_options(-Wall -g)

include_directories(${LVGL_DIR})
include_directories(${LVDRV_DIR})

include(${LVGL_DIR}/CMakeLists.txt)

target_include_directories(lvgl-sdl-demo PUBLIC ${SDL2_INCLUDE_DIRS})
target_compile_options(lvgl-sdl-demo PUBLIC ${SDL2_CFLAGS_OTHER})
target_link_libraries(lvgl-sdl-demo ${SDL2_LIBRARIES} lvglsdl lvgl SDL2)
