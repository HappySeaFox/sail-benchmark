cmake_minimum_required(VERSION 3.10)

project(SAIL-BENCHMARK VERSION 1.0.0
                       DESCRIPTION "Imaging Libraries Benchmarks"
                       LANGUAGES CXX)

macro(add_benchmark_skeleton)
    set(BENCH "${ARGV0}")

    add_executable(${BENCH} src/${BENCH}.cpp)
    target_link_libraries(${BENCH} benchmark::benchmark benchmark::benchmark_main)

    set_target_properties(${BENCH} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${BENCH}")
endmacro()

set(CMAKE_PREFIX_PATH
    "${PROJECT_SOURCE_DIR}/extra/B/lib/cmake/sail"
    ${CMAKE_PREFIX_PATH})

# Required pkg-config
#
set(PKG_CONFIG_EXECUTABLE "${PROJECT_SOURCE_DIR}/extra/bin/pkg-config.exe")
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
find_package(libpng CONFIG REQUIRED)
find_package(CImg CONFIG REQUIRED)

add_benchmark_skeleton(sail-benchmark-cimg)

target_include_directories(sail-benchmark-cimg PRIVATE ${JPEG_INCLUDE_DIR})
target_link_libraries(sail-benchmark-cimg ${JPEG_LIBRARIES})
target_link_libraries(sail-benchmark-cimg png)

target_link_libraries(sail-benchmark-cimg CImg::CImg)

# DevIL
#
pkg_check_modules(IL IMPORTED_TARGET REQUIRED IL)
add_benchmark_skeleton(sail-benchmark-devil)

target_compile_options(sail-benchmark-devil PRIVATE ${IL_CFLAGS})
target_include_directories(sail-benchmark-devil PRIVATE ${IL_INCLUDE_DIRS})
# I failed to add DevIL w/o using this ugly hack (see https://github.com/microsoft/vcpkg/issues/14775)
target_link_libraries(sail-benchmark-devil ${IL_LIBDIR}/DevIL.lib)

# FreeImage
#
find_package(freeimage CONFIG REQUIRED)

add_benchmark_skeleton(sail-benchmark-freeimage)
target_link_libraries(sail-benchmark-freeimage freeimage::FreeImage)

# GIL
#
find_package(Boost REQUIRED)
find_package(JPEG REQUIRED)
find_package(libpng CONFIG REQUIRED)

add_benchmark_skeleton(sail-benchmark-gil)

target_include_directories(sail-benchmark-gil PRIVATE ${JPEG_INCLUDE_DIR})
target_link_libraries(sail-benchmark-gil ${JPEG_LIBRARIES})
target_link_libraries(sail-benchmark-gil png)

target_link_libraries(sail-benchmark-gil Boost::boost)

# OpenImageIO
#
find_package(OpenImageIO CONFIG REQUIRED)

add_benchmark_skeleton(sail-benchmark-openimageio)

target_link_libraries(sail-benchmark-openimageio OpenImageIO::OpenImageIO OpenImageIO::OpenImageIO_Util)

# SAIL
#
find_package(Sail REQUIRED)

add_benchmark_skeleton(sail-benchmark-sail)

target_link_libraries(sail-benchmark-sail SAIL::sail)

# SDL
#
find_package(sdl2 CONFIG REQUIRED)
find_package(sdl2-image CONFIG REQUIRED)

add_benchmark_skeleton(sail-benchmark-sdl)

target_link_libraries(sail-benchmark-sdl SDL2::SDL2_image)

# STB
#
find_path(STB_INCLUDE_DIRS "stb.h")

add_benchmark_skeleton(sail-benchmark-stb)

target_include_directories(sail-benchmark-stb PRIVATE ${STB_INCLUDE_DIRS})

# WIC
#
add_benchmark_skeleton(sail-benchmark-wic)

target_link_libraries(sail-benchmark-wic Windowscodecs)
