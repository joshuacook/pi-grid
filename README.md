# pi-grid

This repository hosts the code for the pi-grid project. The goal is to map grid
inputs to MIDI events and run on a Raspberry Pi.

## macOS Setup

Run the bootstrap script to install Homebrew dependencies. It is safe to run
multiple times as it skips already installed packages.

```bash
./scripts/bootstrap_macos.sh
```

## Building

Build the native `hello` binary using CMake:

```bash
cmake -S . -B build
cmake --build build
```

Apple Silicon users can cross‑compile for Raspberry Pi with the `make pi`
convenience target (uses `cmake/toolchain-arm64.cmake`).

```bash
make pi
```

The resulting binary lives in `build` (or `build-pi` for cross‑compiled) and
simply prints `hello` when executed.

## Raspberry Pi Setup
See [PI_SETUP.md](PI_SETUP.md) for preparing the Pi image and verifying PiSound.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file
for details.
