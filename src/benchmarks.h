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

#pragma once

#define SAIL_ADD_BENCHMARK_WITH_COLOR(suffix) \
BENCHMARK_CAPTURE(BM_##suffix, JPEG_Grey_100x67,  IMAGES "jpeg\\100x67-grey.jpg",  Color::Grey)->Unit(BENCHMARK_UNIT);            \
BENCHMARK_CAPTURE(BM_##suffix, JPEG_YCbCr_100x67, IMAGES "jpeg\\100x67-ycbcr.jpg", Color::YCbCr)->Unit(BENCHMARK_UNIT);           \
BENCHMARK_CAPTURE(BM_##suffix, PNG_Grey_100x71, IMAGES "png\\100x71-grey.png", Color::Grey)->Unit(BENCHMARK_UNIT);                \
BENCHMARK_CAPTURE(BM_##suffix, PNG_RGB_100x71,  IMAGES "png\\100x71-rgb.png",  Color::RGB)->Unit(BENCHMARK_UNIT);                 \
                                                                                                                                  \
BENCHMARK_CAPTURE(BM_##suffix, JPEG_Grey_1000x669,  IMAGES "jpeg\\1000x669-grey.jpg",  Color::Grey)->Unit(BENCHMARK_UNIT);        \
BENCHMARK_CAPTURE(BM_##suffix, JPEG_YCbCr_1000x669, IMAGES "jpeg\\1000x669-ycbcr.jpg", Color::YCbCr)->Unit(BENCHMARK_UNIT);       \
BENCHMARK_CAPTURE(BM_##suffix, PNG_Grey_1000x709, IMAGES "png\\1000x709-grey.png", Color::Grey)->Unit(BENCHMARK_UNIT);            \
BENCHMARK_CAPTURE(BM_##suffix, PNG_RGB_1000x709,  IMAGES "png\\1000x709-rgb.png",  Color::RGB)->Unit(BENCHMARK_UNIT);             \
                                                                                                                                  \
BENCHMARK_CAPTURE(BM_##suffix, JPEG_Grey_6000x4016,  IMAGES "jpeg\\6000x4016-grey.jpg",  Color::Grey)->Unit(BENCHMARK_UNIT);      \
BENCHMARK_CAPTURE(BM_##suffix, JPEG_YCbCr_6000x4016, IMAGES "jpeg\\6000x4016-ycbcr.jpg", Color::YCbCr)->Unit(BENCHMARK_UNIT);     \
BENCHMARK_CAPTURE(BM_##suffix, PNG_Grey_6000x4256, IMAGES "png\\6000x4256-grey.png", Color::Grey)->Unit(BENCHMARK_UNIT);          \
BENCHMARK_CAPTURE(BM_##suffix, PNG_RGB_6000x4256,  IMAGES "png\\6000x4256-rgb.png",  Color::RGB)->Unit(BENCHMARK_UNIT);           \
                                                                                                                                  \
BENCHMARK_CAPTURE(BM_##suffix, JPEG_Grey_15000x10040,  IMAGES "jpeg\\15000x10040-grey.jpg",  Color::Grey)->Unit(BENCHMARK_UNIT);  \
BENCHMARK_CAPTURE(BM_##suffix, JPEG_YCbCr_15000x10040, IMAGES "jpeg\\15000x10040-ycbcr.jpg", Color::YCbCr)->Unit(BENCHMARK_UNIT); \
BENCHMARK_CAPTURE(BM_##suffix, PNG_Grey_15000x10640, IMAGES "png\\15000x10640-grey.png", Color::Grey)->Unit(BENCHMARK_UNIT);      \
BENCHMARK_CAPTURE(BM_##suffix, PNG_RGB_15000x10640,  IMAGES "png\\15000x10640-rgb.png",  Color::RGB)->Unit(BENCHMARK_UNIT);

#define SAIL_ADD_BENCHMARK(suffix) \
BENCHMARK_CAPTURE(BM_##suffix, JPEG_Grey_100x67,  IMAGES "jpeg\\100x67-grey.jpg")->Unit(BENCHMARK_UNIT);            \
BENCHMARK_CAPTURE(BM_##suffix, JPEG_YCbCr_100x67, IMAGES "jpeg\\100x67-ycbcr.jpg")->Unit(BENCHMARK_UNIT);           \
BENCHMARK_CAPTURE(BM_##suffix, PNG_Grey_100x71, IMAGES "png\\100x71-grey.png")->Unit(BENCHMARK_UNIT);               \
BENCHMARK_CAPTURE(BM_##suffix, PNG_RGB_100x71,  IMAGES "png\\100x71-rgb.png")->Unit(BENCHMARK_UNIT);                \
                                                                                                                    \
BENCHMARK_CAPTURE(BM_##suffix, JPEG_Grey_1000x669,  IMAGES "jpeg\\1000x669-grey.jpg")->Unit(BENCHMARK_UNIT);        \
BENCHMARK_CAPTURE(BM_##suffix, JPEG_YCbCr_1000x669, IMAGES "jpeg\\1000x669-ycbcr.jpg")->Unit(BENCHMARK_UNIT);       \
BENCHMARK_CAPTURE(BM_##suffix, PNG_Grey_1000x709, IMAGES "png\\1000x709-grey.png")->Unit(BENCHMARK_UNIT);           \
BENCHMARK_CAPTURE(BM_##suffix, PNG_RGB_1000x709,  IMAGES "png\\1000x709-rgb.png")->Unit(BENCHMARK_UNIT);            \
                                                                                                                    \
BENCHMARK_CAPTURE(BM_##suffix, JPEG_Grey_6000x4016,  IMAGES "jpeg\\6000x4016-grey.jpg")->Unit(BENCHMARK_UNIT);      \
BENCHMARK_CAPTURE(BM_##suffix, JPEG_YCbCr_6000x4016, IMAGES "jpeg\\6000x4016-ycbcr.jpg")->Unit(BENCHMARK_UNIT);     \
BENCHMARK_CAPTURE(BM_##suffix, PNG_Grey_6000x4256, IMAGES "png\\6000x4256-grey.png")->Unit(BENCHMARK_UNIT);         \
BENCHMARK_CAPTURE(BM_##suffix, PNG_RGB_6000x4256,  IMAGES "png\\6000x4256-rgb.png")->Unit(BENCHMARK_UNIT);          \
                                                                                                                    \
BENCHMARK_CAPTURE(BM_##suffix, JPEG_Grey_15000x10040,  IMAGES "jpeg\\15000x10040-grey.jpg")->Unit(BENCHMARK_UNIT);  \
BENCHMARK_CAPTURE(BM_##suffix, JPEG_YCbCr_15000x10040, IMAGES "jpeg\\15000x10040-ycbcr.jpg")->Unit(BENCHMARK_UNIT); \
BENCHMARK_CAPTURE(BM_##suffix, PNG_Grey_15000x10640, IMAGES "png\\15000x10640-grey.png")->Unit(BENCHMARK_UNIT);     \
BENCHMARK_CAPTURE(BM_##suffix, PNG_RGB_15000x10640,  IMAGES "png\\15000x10640-rgb.png")->Unit(BENCHMARK_UNIT);
