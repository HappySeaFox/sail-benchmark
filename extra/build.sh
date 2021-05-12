#!/bin/sh -e

cd "$(dirname "$0")"

########################
#  Common configuation #
########################

cmake_windows_build_type="Release"
cmake_platform_generate_options="-A x64 -DCMAKE_POSITION_INDEPENDENT_CODE=ON"
cmake_platform_build_options="--config $cmake_windows_build_type"

unpack()
{
    local path="$1"
    local name="$(basename "$path")"
    local build="$builddir/$name"

    echo
    echo "Building $path"
    echo

    rm -rf "$build"
    mkdir -p "$build"
    cd "$build"
    tar -zxf "$path" --strip-components=1
}

# Add bin/ dir to PATH to enable nasm etc.
export PATH=$PATH:$PWD/bin

#################
#  Build setup  #
#################

SRC="$PWD/src"
builddir="$PWD/builddir"
B="$PWD/B"

# Clean old builds
rm -rf "$B"
rm -rf "$builddir"

########
# SAIL #
########

src="$SRC/sail-0.9.0-pre14.tar.gz"

unpack "$src"

extra/build

mkdir build
cd build

cmake $cmake_platform_generate_options -DCMAKE_INSTALL_PREFIX="$B" ..
cmake --build . $cmake_platform_build_options --target install

# Clean the build dir
rm -rf "$builddir"

echo
echo Success
echo
