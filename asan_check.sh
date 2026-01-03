#!/bin/bash
# test-asan.sh — проверка памяти через ASan + UBSan с подавлением

set -e

# Убедись, что файл подавлений существует
if [ ! -f .ubsan_suppressions.txt ]; then
    echo "⚠️ Файл .ubsan_suppressions.txt не найден!"
    echo "Создаю базовый..."
    echo "fun:*glfwGetProcAddress*" > .ubsan_suppressions.txt
fi

# Получаем абсолютный путь к корню проекта
PROJECT_ROOT=$(pwd)

echo "⚙️ Сборка ASan+UBSan версии..."
cmake -S . -B build/asan -G Ninja \
  -DCMAKE_C_COMPILER=clang \
  -DCMAKE_CXX_COMPILER=clang++ \
  -DCMAKE_C_FLAGS="-g -O1 -fno-omit-frame-pointer -fsanitize=address,undefined -fsanitize-blacklist=${PROJECT_ROOT}/.ubsan_suppressions.txt" \
  -DCMAKE_CXX_FLAGS="-g -O1 -fno-omit-frame-pointer -fsanitize=address,undefined -fsanitize-blacklist=${PROJECT_ROOT}/.ubsan_suppressions.txt" \
  -DCMAKE_EXE_LINKER_FLAGS="-fsanitize=address,undefined" \
  -DCMAKE_BUILD_TYPE=Debug

cmake --build build/asan

echo "🔍 Запуск..."
ASAN_OPTIONS=detect_leaks=1 ./build/asan/eocc

echo "✅ Утечек не обнаружено!"