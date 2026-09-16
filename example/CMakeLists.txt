cmake_minimum_required(VERSION 3.16)
project(example LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(example_options options.cc)
target_include_directories(example_options PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_options(example_options PRIVATE -Wall -Wextra -Wpedantic)

option(EXAMPLE_WITH_GDK "Build the executable that connects to the robot" ON)
if(DEFINED ENV{GDK_HOME} AND NOT "$ENV{GDK_HOME}" STREQUAL "")
  set(_gdk_default_root "$ENV{GDK_HOME}/app/gdk")
else()
  set(_gdk_default_root "$ENV{HOME}/.cache/agibot/app/gdk")
endif()
set(GDK_ROOT "${_gdk_default_root}" CACHE PATH "Installed GDK root")
set(GDK_EXTRA_LIBRARIES "" CACHE STRING "Additional libraries required by the installed SDK")

if(EXAMPLE_WITH_GDK)
  if(NOT CMAKE_SYSTEM_PROCESSOR MATCHES "^(x86_64|aarch64)$")
    message(FATAL_ERROR "Unsupported GDK architecture: ${CMAKE_SYSTEM_PROCESSOR}")
  endif()
  set(_gdk_cpp_root "${GDK_ROOT}/build_dep/cpp/${CMAKE_SYSTEM_PROCESSOR}")
  find_path(GDK_INCLUDE_DIR gdk/gdk.h HINTS "${_gdk_cpp_root}/include"
            NO_DEFAULT_PATH)
  find_library(GDK_LIBRARY NAMES gdk_adapter HINTS "${_gdk_cpp_root}/lib"
               NO_DEFAULT_PATH)
  if(NOT GDK_INCLUDE_DIR OR NOT GDK_LIBRARY)
    message(FATAL_ERROR
      "GDK headers/libgdk_adapter not found under ${_gdk_cpp_root}. "
      "Set GDK_ROOT, or set GDK_INCLUDE_DIR and GDK_LIBRARY to the actual paths "
      "used by the installed SDK's examples/cpp/CMakeLists.txt.")
  endif()
  message(STATUS "GDK include: ${GDK_INCLUDE_DIR}")
  message(STATUS "GDK adapter: ${GDK_LIBRARY}")
  find_package(Threads REQUIRED)
  add_executable(example main.cc)
  target_include_directories(example PRIVATE "${GDK_INCLUDE_DIR}")
  target_compile_options(example PRIVATE -Wall -Wextra -Wpedantic)
  target_link_libraries(example PRIVATE example_options "${GDK_LIBRARY}"
                        ${GDK_EXTRA_LIBRARIES} Threads::Threads)
endif()

include(CTest)
if(BUILD_TESTING)
  add_executable(options_test options_test.cc)
  target_link_libraries(options_test PRIVATE example_options)
  add_test(NAME options_test COMMAND options_test)
endif()
