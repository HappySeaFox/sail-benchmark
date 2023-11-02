/*  This file is part of SAIL-BENCHMARK (https://github.com/smoked-herring/sail-benchmark)

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

// SAIL
#include <sail/sail.h>
#include <sail-manip/sail-manip.h>

// local
#include "benchmarks.h"
#include "fail.h"

static void BM_SAIL(benchmark::State& state, const char* filename) {
    sail_set_log_barrier(SAIL_LOG_LEVEL_SILENCE);

    SAIL_TRY_OR_EXECUTE(sail_init_with_flags(SAIL_FLAG_PRELOAD_CODECS),
        fail("sail_init_with_flags() failed"));

    for (auto _ : state) {
        sail_image *image;
        SAIL_TRY_OR_EXECUTE(sail_load_from_file(filename, &image),
            fail("Read failed"));

        sail_destroy_image(image);
    }
}

SAIL_ADD_BENCHMARK(SAIL)

BENCHMARK_MAIN();
