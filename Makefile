.DEFAULT_GOAL := build

build:
	cmake -S . -B build
	cmake --build build

pi:
	cmake -S . -B build-pi -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-arm64.cmake
	cmake --build build-pi

clean:
	rm -rf build build-pi
