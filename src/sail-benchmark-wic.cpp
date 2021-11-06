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

#include <memory>

// Windows
#include <windows.h>
#include <wincodec.h>

// local
#include "benchmarks.h"
#include "fail.h"

static void BM_WIC(benchmark::State& state, const char* filename) {
    HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

    if (FAILED(hr)) {
        fail("COM init failed");
    }

    IWICImagingFactory *pWICFactory = nullptr;
    hr = CoCreateInstance(
        CLSID_WICImagingFactory,
        nullptr,
        CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(&pWICFactory)
        );

    if (FAILED(hr)) {
        fail("Component init failed");
    }

    const std::wstring wfilename(filename, filename + strlen(filename) + 1);

    for (auto _ : state) {
        IWICBitmapDecoder *pWICDecoder = nullptr;
        hr = pWICFactory->CreateDecoderFromFilename(
            wfilename.c_str(),
            nullptr,
            GENERIC_READ,
            WICDecodeMetadataCacheOnLoad,
            &pWICDecoder
            );

        if (FAILED(hr)) {
            fail("Init failed");
        }

        IWICBitmapFrameDecode *pWICFrame = nullptr;
        hr = pWICDecoder->GetFrame(0, &pWICFrame);

        if (FAILED(hr)) {
            fail("Get frame failed");
        }

        UINT uiWidth = 0, uiHeight = 0;
        WICPixelFormatGUID pixelFormat; 

        pWICFrame->GetSize(&uiWidth, &uiHeight);
        pWICFrame->GetPixelFormat(&pixelFormat);

        IWICBitmap *pWICBitmap = nullptr;
        hr = pWICFactory->CreateBitmapFromSource(pWICFrame, WICBitmapCacheOnLoad, &pWICBitmap);

        if (FAILED(hr)) {
            fail("Bitmap creation failed");
        }

        pWICBitmap->Release();

        pWICFrame->Release();
        pWICDecoder->Release();
    }
}

SAIL_ADD_BENCHMARK(WIC)

BENCHMARK_MAIN();
