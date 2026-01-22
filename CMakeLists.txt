cmake_minimum_required(VERSION 3.18)

if (NOT WIN32)
    #message(FATAL_ERROR "This project currently runs on Windows only")
endif()

# Set vcpkg toolchain
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/../vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

project(SAIL-BENCHMARK VERSION 1.1.0
                       DESCRIPTION "Imaging Libraries Benchmarks"
                       LANGUAGES CXX)

macro(add_benchmark_skeleton)
    set(BENCH "${ARGV0}")

    add_executable(${BENCH} src/${BENCH}.cpp)
    target_link_libraries(${BENCH} benchmark::benchmark benchmark::benchmark_main)

    set_target_properties(${BENCH} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${BENCH}")
endmacro()

find_package(PkgConfig REQUIRED)

find_package(benchmark CONFIG REQUIRED)

# Path to test images
#
set(IMAGES "${PROJECT_SOURCE_DIR}/images/")
string(REPLACE "/" "\\\\" IMAGES "${IMAGES}")
add_definitions(-DIMAGES="${IMAGES}")

# Benchmark units
#
add_definitions(-DBENCHMARK_UNIT=benchmark::kMicrosecond)

#
# Benchmarks
#

# CImg
#
find_package(JPEG REQUIRED)
find_package(PNG REQUIRED)
find_package(CImg CONFIG REQUIRED)

add_benchmark_skeleton(sail-benchmark-cimg)

target_compile_definitions(sail-benchmark-cimg PRIVATE cimg_display=0)
target_link_libraries(sail-benchmark-cimg JPEG::JPEG PNG::PNG CImg::CImg)

# DevIL
#
if (WIN32)
    pkg_check_modules(IL IMPORTED_TARGET REQUIRED DevIL)
else()
    pkg_check_modules(IL IMPORTED_TARGET REQUIRED IL)
endif()
find_package(JPEG REQUIRED)
find_package(PNG REQUIRED)
find_package(TIFF REQUIRED)
find_library(JASPER_LIBRARY jasper REQUIRED)

#add_benchmark_skeleton(sail-benchmark-devil)

#target_link_libraries(sail-benchmark-devil PkgConfig::IL JPEG::JPEG PNG::PNG TIFF::TIFF ${JASPER_LIBRARY})

# FreeImage
#
find_package(freeimage CONFIG REQUIRED)

add_benchmark_skeleton(sail-benchmark-freeimage)
target_link_libraries(sail-benchmark-freeimage freeimage::FreeImage)

# gdk-pixbuf
#
pkg_check_modules(GDK_PIXBUF IMPORTED_TARGET REQUIRED gdk-pixbuf-2.0)

add_benchmark_skeleton(sail-benchmark-gdk-pixbuf)

target_link_libraries(sail-benchmark-gdk-pixbuf PkgConfig::GDK_PIXBUF)

# GIL
#
find_package(Boost REQUIRED)
find_package(JPEG REQUIRED)
find_package(PNG REQUIRED)

add_benchmark_skeleton(sail-benchmark-gil)

target_link_libraries(sail-benchmark-gil JPEG::JPEG PNG::PNG Boost::boost)

# GraphicsMagick
#
pkg_check_modules(GMAGICK IMPORTED_TARGET REQUIRED GraphicsMagick++)

add_benchmark_skeleton(sail-benchmark-graphicsmagick)

target_link_libraries(sail-benchmark-graphicsmagick PkgConfig::GMAGICK)

# OpenCV
#
find_package(OpenCV CONFIG REQUIRED)

add_benchmark_skeleton(sail-benchmark-opencv)

target_link_libraries(sail-benchmark-opencv opencv_core opencv_imgcodecs)

# OpenImageIO
#
find_package(OpenImageIO CONFIG REQUIRED)

add_benchmark_skeleton(sail-benchmark-openimageio)

target_link_libraries(sail-benchmark-openimageio OpenImageIO::OpenImageIO OpenImageIO::OpenImageIO_Util)

# SAIL
#
find_package(Sail REQUIRED)
find_package(SailManip REQUIRED)

add_benchmark_skeleton(sail-benchmark-sail)

target_link_libraries(sail-benchmark-sail SAIL::sail SAIL::sail-manip)

# SDL
#
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)

add_benchmark_skeleton(sail-benchmark-sdl)

target_link_libraries(sail-benchmark-sdl
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)

target_link_libraries(sail-benchmark-sdl
    $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
)

# STB
#
find_path(STB_INCLUDE_DIRS "stb_image.h" REQUIRED)

add_benchmark_skeleton(sail-benchmark-stb)

target_include_directories(sail-benchmark-stb PRIVATE ${STB_INCLUDE_DIRS})

# WIC (Windows only)
#
if (WIN32)
    add_benchmark_skeleton(sail-benchmark-wic)

    target_link_libraries(sail-benchmark-wic Windowscodecs)
endif()
