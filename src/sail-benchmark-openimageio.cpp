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

#include <memory>

// OpenImageIO
#include <OpenImageIO/imageio.h>
using namespace OIIO;

// local
#include "benchmarks.h"
#include "fail.h"

static void BM_OpenImageIO(benchmark::State& state, const char* filename) {
    // Preload codec
    auto outer = ImageInput::open(filename);

    if (!outer) {
        fail("Read failed");
    }

    for (auto _ : state) {
        auto in = ImageInput::open(filename);

        if (!in) {
            fail("Read failed");
        }

        const ImageSpec &spec = in->spec();

        const auto imageSize = spec.width * spec.height * spec.nchannels;
        auto pixels = std::make_unique<unsigned char[]>(imageSize);

        in->read_image(0, 0, 0, spec.nchannels, TypeDesc::UINT8, pixels.get());

        in->close();
    }
}

SAIL_ADD_BENCHMARK(OpenImageIO)

BENCHMARK_MAIN();
