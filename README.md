# pi-grid

This repository hosts the code for the pi-grid project. The goal is to map grid inputs to MIDI events and run on a Raspberry Pi.

## Getting Started

This repository currently provides a minimal C build using CMake.  To build the
`hello` binary locally, run the following commands from the project root:

```bash
cmake -S . -B build
cmake --build build
```

To cross-compile for an ARM target (e.g. Raspberry Pi), you will need the
`aarch64-linux-gnu-gcc` toolchain installed.  Pass the provided toolchain file:

```bash
cmake -S . -B build-arm64 -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-arm64.cmake
cmake --build build-arm64
```

The binary will be created at `build/hello` and simply prints `hello` when
executed.  More functionality will land in subsequent epics.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
