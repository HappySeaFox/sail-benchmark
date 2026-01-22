/*  This file is part of SAIL-BENCHMARK (https://github.com/HappySeaFox/sail-benchmark)

    Copyright (c) 2020 Dmitry Baryshev

    The MIT License

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#include <benchmark/benchmark.h>

// GIL
#include <boost/gil.hpp>
#include <boost/gil/extension/dynamic_image/any_image.hpp>
#include <boost/gil/extension/io/jpeg.hpp>
#include <boost/gil/extension/io/png.hpp>

// local
#include "benchmarks.h"
#include "fail.h"

static bool endsWith(const char* src, const char* str) {
    const size_t src_len = strlen(src);
    const size_t str_len = strlen(str);

    return strcmp(src + (src_len - str_len), str) == 0;
}

static void BM_GIL(benchmark::State& state, const char* filename) {
    bool isJpeg = false;
    bool isPng = false;

    if (endsWith(filename, "jpg")) {
        isJpeg = true;
    } else if (endsWith(filename, "png")) {
        isPng = true;
    } else {
        fail("Unsupported file suffix");
    }

    for (auto _ : state) {
        try {
            boost::gil::any_image<
                boost::gil::gray8_image_t,
                boost::gil::gray16_image_t,
                boost::gil::rgb8_image_t,
                boost::gil::rgb16_image_t,
                boost::gil::rgba8_image_t,
                boost::gil::rgba16_image_t
            > image;

            if (isJpeg) {
                boost::gil::read_image(filename, image, boost::gil::jpeg_tag());
            } else if (isPng) {
                boost::gil::read_image(filename, image, boost::gil::png_tag());
            }
        } catch (std::exception ex) {
            std::cerr << ex.what() << std::endl;
            throw;
        }
    }
}

SAIL_ADD_BENCHMARK(GIL)

BENCHMARK_MAIN();
