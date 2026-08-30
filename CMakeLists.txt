cmake_minimum_required(VERSION 3.25)
project(doom_fire VERSION 1.0.0 LANGUAGES CXX)

add_executable(doom_fire)

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

target_sources(doom_fire
  PRIVATE
    main.cpp
    Application.cpp
    utilities.cpp

  PUBLIC
    FILE_SET HEADERS
)

target_link_libraries(doom_fire
  PRIVATE
    SDL3::SDL3
)

target_compile_features(doom_fire
  PRIVATE
    cxx_std_26
)

target_compile_options(doom_fire
  PRIVATE
    -Wall
    -Wextra
    -pedantic
    -Werror
    -stdlib=libc++
)

target_link_options(doom_fire
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

target_compile_features(unit_tests
  PRIVATE
    cxx_std_26
)

add_test(
  NAME    unit_tests
  COMMAND unit_tests
)
