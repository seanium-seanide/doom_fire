cmake_minimum_required(VERSION 3.25)
project(sdl3_pixels VERSION 1.0.0 LANGUAGES CXX)

add_executable(sdl3_pixels)

include(FetchContent)

FetchContent_Declare(
  SDL3
  URL       https://github.com/libsdl-org/SDL/releases/download/release-3.4.14/SDL3-3.4.14.tar.gz
  URL_HASH  SHA256=30d4aa2b3037718142b32dffd4e72f917ebb6cc5227150e7bb9c45efb2153aeb
)
FetchContent_MakeAvailable(SDL3)

target_sources(sdl3_pixels
  PRIVATE
    main.cpp
    Application.cpp
    utilities.cpp

  PUBLIC
    FILE_SET HEADERS
)

target_link_libraries(sdl3_pixels
  PRIVATE
    SDL3::SDL3
)

target_compile_features(sdl3_pixels
  PRIVATE
    cxx_std_26
)

target_compile_options(sdl3_pixels
  PRIVATE
    -Wall
    -Wextra
    -pedantic
    -Werror
    -stdlib=libc++
)

target_link_options(sdl3_pixels
  PRIVATE
    -stdlib=libc++
)
