#!/bin/sh -e

cd "$(dirname "$0")"

tests="
sail-benchmark-cimg
sail-benchmark-devil
sail-benchmark-freeimage
sail-benchmark-gil
sail-benchmark-openimageio
sail-benchmark-sail
sail-benchmark-sdl
sail-benchmark-stb
sail-benchmark-wic"

images="
JPEG_Gray_100x67
JPEG_YCbCr_100x67
PNG_Gray_100x71
PNG_RGBA_100x71
JPEG_Gray_1000x669
JPEG_YCbCr_1000x669
PNG_Gray_1000x709
PNG_RGBA_1000x709
JPEG_Gray_6000x4016
JPEG_YCbCr_6000x4016
PNG_Gray_6000x4256
PNG_RGBA_6000x4256
JPEG_Gray_15000x10040
JPEG_YCbCr_15000x10040
PNG_Gray_15000x10640
PNG_RGBA_15000x10640"

# Must be greater than 1 to calculate mean time
#
repetitions="5"

results=".results"

##################

rm -rf $results
mkdir $results

for image in $images; do
    result=$(echo "$results/${image}.txt" | sed "s|_|-|g")

    for test in $tests; do
        echo "Running $test/$image..."

        # Take the mean time
        build/${test}/Release/${test} --benchmark_repetitions=$repetitions --benchmark_filter="$image" 2>/dev/null | \
            grep _mean | sed "s|BM_||;s|/${image}_mean||" | awk '{print $1 " " $2}' >> ${result}.tmp || true # SDL test returns 2 from SDL_Main
    done

    # Sort the result
    cat ${result}.tmp | sort -n -k 2 > ${result}
    rm -f ${result}.tmp
done
