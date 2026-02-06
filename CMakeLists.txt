cmake_minimum_required(VERSION 3.20)
project(Chess)

#use modern C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#build static SDL
set(SDL_SHARED OFF   CACHE BOOL "" FORCE)
set(SDL_STATIC ON    CACHE BOOL "" FORCE)
set(SDL_TESTS OFF    CACHE BOOL "" FORCE)
set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SDL_INSTALL OFF  CACHE BOOL "" FORCE)
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/SDL EXCLUDE_ALL)

#default to release
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

add_executable(${PROJECT_NAME}
  main.cpp

  #src
  src/game.cpp

  #include
  include/game.hpp
  include/settings.hpp
  include/settings.hpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3-static)

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
