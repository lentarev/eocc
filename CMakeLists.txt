cmake_minimum_required(VERSION 3.28)

# Язык проекта — только C и C++
project(eocc LANGUAGES C CXX)

# --- Подключаем GLFW из third_party ---
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
option(GLFW_BUILD_DOCS OFF)
option(GLFW_INSTALL OFF)
option(GLFW_BUILD_SHARED_LIBS OFF)  # ← ключевая строка: делаем статическую библиотеку
set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "" FORCE)  # ← отключаем Wayland
add_subdirectory(third_party/glfw-3.4)

# --- Подключаем SOIL2 как подпроект ---
# Отключаем примеры и тесты (если они есть)
set(BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(third_party/SOIL2)


# --- Подключаем OpenGL ---
find_package(OpenGL REQUIRED)

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

# ===============================
# СОБИРАЕМ ДВИЖОК как библиотеку
# ===============================

# Ищем все .cpp и .c файлы движка + glad
file(GLOB_RECURSE ENGINE_SOURCES
    src/engine/*.cpp
    src/engine/*.c
    third_party/glad/src/glad.c
)

# Создаём статическую библиотеку движка
add_library(eocc_engine STATIC ${ENGINE_SOURCES})

# Важно: указываем, что заголовки из third_party доступны как <...>
target_include_directories(eocc_engine
    PUBLIC
        ${CMAKE_SOURCE_DIR}/third_party/glad/include        # для #include <glad/glad.h>
		${CMAKE_SOURCE_DIR}/third_party/glfw-3.4/include    # для #include <engine/base/logger.h> и т.д.
		${CMAKE_SOURCE_DIR}/third_party/glm
        ${CMAKE_SOURCE_DIR}/src                             
)

# --- Цель ---
add_executable(eocc src/main.cpp)

# Игра зависит от движка
target_link_libraries(eocc PRIVATE eocc_engine OpenGL::GL glfw)

# Игра также может использовать заголовки движка (если нужно)
target_include_directories(eocc
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)

# Применяем C++20 к движку
target_compile_features(eocc_engine PUBLIC cxx_std_20)

# --- Свойства цели (лучше так, чем глобальные флаги) ---
target_compile_features(eocc PRIVATE cxx_std_20)

# Если позже добавите OpenGL, GLFW, assimp и т.д. — подключайте так:
# target_link_libraries(eocc PRIVATE OpenGL::GL glfw assimp::assimp)