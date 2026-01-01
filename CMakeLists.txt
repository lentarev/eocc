cmake_minimum_required(VERSION 3.31)

# Язык проекта — только C и C++
project(eocc LANGUAGES C CXX)

# --- Стандарт C++ ---
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # ЗАПРЕЩАЕМ vendor-extensions (GNU, MSVC и т.д.)

# Рекомендуется для новых проектов (использовать GLVND, если доступен)
cmake_policy(SET CMP0072 NEW)

# --- Компилятор и флаги ---
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # Общие флаги для всех платформ
    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
        -Wno-unused-parameter
    )

    # Отладочные флаги (для Debug и ASan)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
        add_compile_options(-g -fno-omit-frame-pointer)
    endif()

    # Санитайзеры (ASan автоматически включается через флаги в CMakePresets.json)
    # Ничего дополнительно не нужно — флаги уже приходят из preset'а

endif()

# --- Компоновка ---
# На Windows с MinGW-w64: используем современные флаги линковки
if(WIN32 AND CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # Обязательно: консольное приложение
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mconsole")
    # Для Unicode (опционально, но рекомендуется)
    add_compile_options(-municode)
endif()

# --- Цель ---
add_executable(eocc src/main.cpp)

# --- Свойства цели (лучше так, чем глобальные флаги) ---
target_compile_features(eocc PRIVATE cxx_std_20)

# Если позже добавите OpenGL, GLFW, assimp и т.д. — подключайте так:
# target_link_libraries(eocc PRIVATE OpenGL::GL glfw assimp::assimp)