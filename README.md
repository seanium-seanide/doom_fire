# README

A C++ implementation of the classic Doom fire algorithm

![Video](assets/video.webp)

## Building and running on linux:

### Prerequisites

The project must be built with C++26 support turned on.

The project has only been tested under linux with clang and gcc. The project *should* build under MacOS.

As of 30/08/2026, the project is not expected to build successfully via MSVC in Microsoft Windows due to lack of
support for the multi-argument index operator introduced in C++26, and used with `mdspan`. There are no obvious
reasons  why the project should not build successfully via Clang under Microsoft Windows.

* **clang++-22 and libc++-22** or **g++-16 and libstdc++-16**
* CMake >= 3.25

### Building

#### clang

```
cmake --build --preset build-debug-clang # Debug configuration

or

cmake --build --preset build-release-clang # Release configuration
```

#### gcc

```
cmake --build --preset build-debug-gcc # Debug configuration

or

cmake --build --preset build-release-gcc # Release configuration
```

### Running

#### clang

```
./build/debug/clang/source/doom_fire # Debug configuration

or

./build/release/clang/source/doom_fire # Release configuration
```

#### gcc

```
./build/debug/gcc/source/doom_fire # Debug configuration

or

./build/release/gcc/source/doom_fire # Release configuration
```
