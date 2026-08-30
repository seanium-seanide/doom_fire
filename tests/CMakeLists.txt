add_executable(unit_tests)
target_sources(unit_tests
  PRIVATE
    unit_tests.cpp

  PUBLIC
    FILE_SET HEADERS
      BASE_DIRS
        ${DOOM_FIRE_INCLUDE_DIRECTORY}
)
target_link_libraries(unit_tests
  PRIVATE
    utilities_lib
    Catch2::Catch2WithMain
)
target_compile_features(unit_tests
  PRIVATE
    cxx_std_26
)
target_compile_options(unit_tests
  PRIVATE
    -Wall
    -Wextra
    -pedantic
    -Werror
)
add_test(
  NAME    unit_tests
  COMMAND unit_tests
)
