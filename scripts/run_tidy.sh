#!/usr/bin/env bash
set -e

files=$(git ls-files '*.c')

for f in $files; do
    clang-tidy "$f" -- -Iinclude
done
