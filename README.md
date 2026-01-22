# Imaging libraries benchmark

This is a collection of benchmarks to measure image loading times across different C/C++ imaging libraries.

Google Benchmark is used as the benchmarking framework.

The benchmarks use JPEG and PNG files as input with four different resolutions, grey and RGB.

Target platform: Windows x64 with MSVC 2019+.

Any contributions are highly welcomed.

## Tested libraries

The benchmarks test image loading (decoding) performance. Each library loads images using its default settings without pixel format conversions.

- [Boost.GIL](https://www.boost.org/doc/libs/1_68_0/libs/gil/doc/html/index.html)
- [CImg](https://github.com/dtschump/CImg)
- [DevIL](http://openil.sourceforge.net)
- [FreeImage](https://freeimage.sourceforge.io)
- [gdk-pixbuf](https://gitlab.gnome.org/GNOME/gdk-pixbuf)
- [GraphicsMagick](http://www.graphicsmagick.org/)
- [OpenCV](https://opencv.org/)
- [OpenImageIO](https://github.com/OpenImageIO/oiio.git)
- [SAIL](https://github.com/HappySeaFox/sail)
- [SDL_Image](https://www.libsdl.org/projects/SDL_image)
- [stb_image](https://github.com/nothings/stb)
- [WIC (Windows only)](https://docs.microsoft.com/en-us/windows/win32/wic/-wic-about-windows-imaging-codec)

## Building

Install `vcpkg` following the [official instructions](https://github.com/microsoft/vcpkg). Install CMake.

Clone vcpkg to `../vcpkg/` relative to the project directory:

```bash
cd ..
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh  # Linux/Mac
# or
bootstrap-vcpkg.bat   # Windows
```

All dependencies are managed through vcpkg. The project includes a `vcpkg.json` manifest file that will automatically install required packages when configuring with CMake.

Build the project:

```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release
```

## Running

Run all benchmarks:

```bash
./run-benchmarks.sh
```

## License

Released under the MIT license.

```
Copyright (c) 2020-2026 Dmitry Baryshev

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
```
