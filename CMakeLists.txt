cmake_minimum_required(VERSION 3.20)
project(Chess)

#use modern C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#sdl
find_package(SDL3 REQUIRED)

#default to debug
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

add_executable(${PROJECT_NAME}
  main.cpp

  #src
  src/game.cpp
  src/board.cpp
  src/piece.cpp
  src/assetmanager.cpp
  src/moves.cpp

  #include
  include/game.hpp
  include/settings.hpp
  include/board.hpp
  include/types.hpp
  include/piece.hpp
  include/assetmanager.hpp
  include/moves.hpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  SDL3::SDL3)

#expose assets
target_compile_definitions(${PROJECT_NAME} PRIVATE
  ASSETS_PATH="${CMAKE_SOURCE_DIR}/assets"
)

target_include_directories(${PROJECT_NAME} PRIVATE
  ${PROJECT_SOURCE_DIR}/include)

target_compile_options(${PROJECT_NAME} PRIVATE
  $<$<CXX_COMPILER_ID:GNU,Clang>:
    -Wall
    -Wextra
    -Wpedantic
  >
  $<$<CXX_COMPILER_ID:MSVC>:
    /W4
    /permissive-
  >
)
