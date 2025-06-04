#!/usr/bin/env bash
set -e

REQUIRED=(libmonome alsa-lib pkg-config cmake aarch64-linux-gnu-gcc)

if ! command -v brew >/dev/null 2>&1; then
  echo "Homebrew not found. Please install Homebrew from https://brew.sh/" >&2
  exit 1
fi

for pkg in "${REQUIRED[@]}"; do
  if brew list "$pkg" >/dev/null 2>&1; then
    echo "[bootstrap] $pkg already installed"
  else
    echo "[bootstrap] Installing $pkg"
    brew install "$pkg"
  fi
done

echo "[bootstrap] Done. Open a new terminal to ensure PATH updates take effect."
