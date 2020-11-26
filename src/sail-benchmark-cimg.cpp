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

// CImg
#define cimg_use_jpeg
#define cimg_use_png

#include <CImg.h>
using namespace cimg_library;

// local
#include "benchmarks.h"
#include "color.h"
#include "fail.h"

static void BM_CImg(benchmark::State& state, const char* filename, Color color) {
    for (auto _ : state) {
        using Image = CImg<unsigned char>;
        Image image(filename);

        switch (color) {
            case Color::YCbCr: {
                image.YCbCrtoRGB();
                break;
            }

            case Color::Grey: {
                Image copy(image.width(), image.height(), 1, 4, 0);
                const unsigned char *src = image.data(0,0,0,0);
                unsigned char *p1 = copy.data(0,0,0,0), *p2 = copy.data(0,0,0,1), *p3 = copy.data(0,0,0,2), *p4 = copy.data(0,0,0,3);

                const Image::longT imageSize = (Image::longT)image.width() * image.height() * 1;

                cimg_pragma_openmp(parallel for cimg_openmp_if_size(imageSize, 512))
                for (Image::longT N = 0; N < imageSize; ++N) {
                    p1[N] = src[N];
                    p2[N] = src[N];
                    p3[N] = src[N];
                    p4[N] = 255;
                }
                break;
            }
        }
    }
}

SAIL_ADD_BENCHMARK_WITH_COLOR(CImg)

BENCHMARK_MAIN();
