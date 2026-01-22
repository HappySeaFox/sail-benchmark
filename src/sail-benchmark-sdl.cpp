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

// SDL_image
#include <SDL_image.h>

// local
#include "benchmarks.h"
#include "fail.h"

constexpr int SDL_FILETYPE = IMG_INIT_PNG | IMG_INIT_JPG;

static void BM_SDL(benchmark::State& state, const char* filename) {
    if ((IMG_Init(SDL_FILETYPE) & SDL_FILETYPE) == 0) {
        std::cerr << IMG_GetError() << std::endl;
        fail("Failed to initialize image");
    }

    for (auto _ : state) {
        SDL_Surface *image = IMG_Load(filename);

        if (image == nullptr) {
            std::cerr << IMG_GetError() << std::endl;
            fail("Read failed");
        }

        SDL_FreeSurface(image);
    }
}

SAIL_ADD_BENCHMARK(SDL)

BENCHMARK_MAIN();
