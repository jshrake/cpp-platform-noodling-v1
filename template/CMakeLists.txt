cmake_minimum_required (VERSION 3.2.0)
project (GRIM_NAME)

# Build the main executable
include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)

set(GRIM_SANITIZERS
  "" CACHE STRING "Clang sanitizers")

add_executable (GRIM_NAME
  src/grim_game.cpp
)

target_compile_definitions(GRIM_NAME PRIVATE
  GRIM_HOT_RELOAD=1
)

target_include_directories(GRIM_NAME PRIVATE
  ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(GRIM_NAME
  ${SDL2_LIBRARIES}
  ${GRIM_SANITIZERS}
)

target_compile_options(GRIM_NAME PRIVATE
  -Wall
  -Wextra
  -Werror
  -Wno-unused-function
  -fno-omit-frame-pointer
)

# Build the game
add_library(GRIM_NAME_lib SHARED
  src/GRIM_NAME.cpp
)

if(APPLE)
find_package(OpenGL REQUIRED)
target_link_libraries(GRIM_NAME_lib
  ${OPENGL_LIBRARIES}
)
target_include_directories(GRIM_NAME_lib PRIVATE
  ${OPENGL_INCLUDE_DIR}
)
endif()

target_link_libraries(GRIM_NAME_lib
  ${GRIM_SANITIZERS}
)

target_compile_options(GRIM_NAME_lib PRIVATE
  -Wall
  -Wextra
  -Werror
  -Wno-old-style-cast
  -fno-omit-frame-pointer
  -Wno-unused-const-variable
  -Wno-unused-variable
  -Wno-unused-parameter
  -Wno-unused-function
)
