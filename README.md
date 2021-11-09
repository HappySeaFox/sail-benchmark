# Imaging libraries benchmark

This is a collection of benchmarks to measure images loading times across different C/C++ imaging libraries.

Google Benchmark is used as a benchmarking framework.

The benchmarks use JPEG and PNG files as input with four different resolutions, grey and RGB.

Target platform: Windows x64 with MSVS 2019.

Any contributions are highly welcomed.

## Tested libraries

- [Boost.GIL](https://www.boost.org/doc/libs/1_68_0/libs/gil/doc/html/index.html)
- [CImg](https://github.com/dtschump/CImg)
- [DevIL](http://openil.sourceforge.net)
- [FreeImage](https://freeimage.sourceforge.io)
- [OpenImageIO](https://github.com/OpenImageIO/oiio.git)
- [SAIL](https://github.com/smoked-herring/sail)
- [SDL_Image](https://www.libsdl.org/projects/SDL_image)
- [stb_image](https://github.com/nothings/stb)
- [WIC (Windows only)](https://docs.microsoft.com/en-us/windows/win32/wic/-wic-about-windows-imaging-codec)

## Building

Install `vcpkg` following the official instructions. Install MSVS 2019 and CMake.

Build extra dependencies in Git Bash:

```
extra/build.sh
```

In Git Bash or cmd:

```
VCPKG_INSTALL_PATH\vcpkg install libjpeg-turbo libpng benchmark cimg devil freeimage boost-gil openimageio sdl2-image[libjpeg-turbo] stb --triplet x64-windows

mkdir build
cd build
cmake -A x64 -DCMAKE_TOOLCHAIN_FILE=VCPKG_INSTALL_PATH\scripts\buildsystems\vcpkg.cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release
```

## Running

In Git Bash:

```
./run-all.sh
```

## License

Released under the MIT license.

```
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
```
