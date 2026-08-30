add_library(debug_options INTERFACE)
target_compile_options(debug_options
  INTERFACE
    "$<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CONFIG:Debug>>:-Og;-g>"
    "$<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CONFIG:Release>>:-O3;-DNDEBUG>"
)


add_library(doom_fire_lib)
target_sources(doom_fire_lib
  PRIVATE
    Application.cpp

  PUBLIC FILE_SET HEADERS
    BASE_DIRS
      ${DOOM_FIRE_INCLUDE_DIRECTORY}
)
target_link_libraries(doom_fire_lib
  PUBLIC
    SDL3::SDL3

  PRIVATE
    debug_options
)
target_compile_features(doom_fire_lib
  PUBLIC
    cxx_std_26
)
target_compile_options(doom_fire_lib
  PRIVATE
    -Wall
    -Wextra
    -pedantic
    -Werror

  PUBLIC
    "$<$<COMPILE_LANG_AND_ID:CXX,Clang,AppleClang>:-stdlib=libc++>"
)
target_link_options(doom_fire_lib
  PUBLIC
    "$<$<LINK_LANG_AND_ID:CXX,Clang,AppleClang>:-stdlib=libc++>"
)


add_library(utilities_lib)
target_sources(utilities_lib
  PRIVATE
    utilities.cpp

  PUBLIC FILE_SET HEADERS
    BASE_DIRS
      ${DOOM_FIRE_INCLUDE_DIRECTORY}
)
target_link_libraries(utilities_lib
  PRIVATE
    debug_options
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
    debug_options
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
    "$<$<COMPILE_LANG_AND_ID:CXX,Clang,AppleClang>:-stdlib=libc++>"
)
target_link_options(doom_fire
  PRIVATE
    "$<$<LINK_LANG_AND_ID:CXX,Clang,AppleClang>:-stdlib=libc++>"
)
