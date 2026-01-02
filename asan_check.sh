#!/bin/bash
# test-asan.sh — проверка памяти через ASan на Linux

set -e  # остановить при первой ошибке

echo "⚙️ Сборка ASan версии..."
cmake -S . -B build/asan -G Ninja \
  -DCMAKE_C_COMPILER=clang \
  -DCMAKE_CXX_COMPILER=clang++ \
  -DCMAKE_C_FLAGS="-g -O1 -fno-omit-frame-pointer -fsanitize=address,undefined" \
  -DCMAKE_CXX_FLAGS="-g -O1 -fno-omit-frame-pointer -fsanitize=address,undefined" \
  -DCMAKE_EXE_LINKER_FLAGS="-fsanitize=address,undefined" \
  -DCMAKE_BUILD_TYPE=Debug

cmake --build build/asan

echo "🔍 Запуск с проверкой утечек..."
# ASAN_OPTIONS=detect_leaks=1:abort_on_error=1 ./build/asan/eocc
ASAN_OPTIONS=detect_leaks=1 ./build/asan/eocc

echo "✅ Утечек не обнаружено!"