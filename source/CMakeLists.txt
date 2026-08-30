add_library(doom_fire_lib)
target_sources(doom_fire_lib
  PRIVATE
    main.cpp
    Application.cpp

  PUBLIC FILE_SET HEADERS
    BASE_DIRS
      ${DOOM_FIRE_INCLUDE_DIRECTORY}
)
target_link_libraries(doom_fire_lib
  PRIVATE
    SDL3::SDL3
)
target_compile_features(doom_fire_lib
  PRIVATE
    cxx_std_26
)
target_compile_options(doom_fire_lib
  PRIVATE
    -Wall
    -Wextra
    -pedantic
    -Werror
    -stdlib=libc++
)
target_link_options(doom_fire_lib
  PRIVATE
    -stdlib=libc++
)


add_library(utilities_lib)
target_sources(utilities_lib
  PRIVATE
    utilities.cpp

  PUBLIC FILE_SET HEADERS
    BASE_DIRS
      ${DOOM_FIRE_INCLUDE_DIRECTORY}
)
target_compile_features(utilities_lib
  PRIVATE
    cxx_std_26
)
target_compile_options(utilities_lib
  PRIVATE
    -Wall
    -Wextra
    -pedantic
    -Werror
)


add_executable(doom_fire)
target_sources(doom_fire
  PRIVATE
    main.cpp
)
target_link_libraries(doom_fire
  PRIVATE
    doom_fire_lib
    utilities_lib
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
