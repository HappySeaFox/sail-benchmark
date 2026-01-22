/*  This file is part of SAIL-BENCHMARK (https://github.com/HappySeaFox/sail-benchmark)

    Copyright (c) 2026 Dmitry Baryshev

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

// OpenCV
#include <opencv2/opencv.hpp>

// local
#include "benchmarks.h"
#include "fail.h"

static void BM_OpenCV(benchmark::State& state, const char* filename) {
    for (auto _ : state) {
        cv::Mat image = cv::imread(filename, cv::IMREAD_UNCHANGED);

        if (image.empty()) {
            fail("Read failed");
        }
    }
}

SAIL_ADD_BENCHMARK(OpenCV)

BENCHMARK_MAIN();
