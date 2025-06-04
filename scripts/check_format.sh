#!/usr/bin/env bash
set -e

files=$(git ls-files '*.c' '*.h')

need_fmt=0
for f in $files; do
    if ! clang-format -style=file "$f" | diff -u "$f" - >/dev/null; then
        echo "File $f is not properly formatted"
        need_fmt=1
    fi
done

exit $need_fmt
