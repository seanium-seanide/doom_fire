cmake_minimum_required(VERSION 3.25)
project(doom_fire VERSION 1.0.0 LANGUAGES CXX)

option(BUILD_TESTING "Build unit tests" ON)
include(FetchDependencies.cmake)
set(DOOM_FIRE_INCLUDE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(source)

if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()
