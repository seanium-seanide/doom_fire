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

FetchContent_Declare(
  Catch2
  URL       https://github.com/catchorg/Catch2/archive/refs/tags/v3.15.3.tar.gz
  URL_HASH  SHA256=b0299ae552918220a7a6e21e7de5b714777f4e8c883fb70c4bb23fe01df8c6e3
)
FetchContent_MakeAvailable(Catch2)

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

enable_testing()

add_executable(unit_tests)

target_sources(unit_tests
  PRIVATE
    utilities.cpp
    unit_tests.cpp

  PUBLIC
    FILE_SET HEADERS
)

target_link_libraries(unit_tests
  PRIVATE
    Catch2::Catch2WithMain
)

add_test(
  NAME    unit_tests
  COMMAND unit_tests
)
