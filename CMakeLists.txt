cmake_minimum_required(VERSION 3.20)
project(stochastic_systems_lab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE EXERCISE_MAINS CONFIGURE_DEPENDS
     "${CMAKE_SOURCE_DIR}/src/*/main.cpp")

add_library(mocc STATIC
    "${CMAKE_SOURCE_DIR}/src/mocc/time.cpp")
target_include_directories(mocc PUBLIC
    "${CMAKE_SOURCE_DIR}/include")
target_compile_options(mocc PRIVATE -Wall -Wextra -pedantic)

foreach(main_file IN LISTS EXERCISE_MAINS)
  get_filename_component(exercise_dir "${main_file}" DIRECTORY)
  file(RELATIVE_PATH exercise_name "${CMAKE_SOURCE_DIR}/src" "${exercise_dir}")
  string(REPLACE "/" "_" target_name "${exercise_name}")

  file(GLOB exercise_sources CONFIGURE_DEPENDS "${exercise_dir}/*.cpp")

  add_executable(${target_name} ${exercise_sources})
  target_include_directories(${target_name} PRIVATE
      "${CMAKE_SOURCE_DIR}/include")
  if(exercise_name MATCHES "^.*/2026-01-14-ex[1-5]$")
    target_link_libraries(${target_name} PRIVATE mocc)
  endif()
  target_compile_options(${target_name} PRIVATE -Wall -Wextra -pedantic)
endforeach()
