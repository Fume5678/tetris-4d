cmake_minimum_required(VERSION 3.11)

set(This tetris_4d)
project(${This})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)

# Raylib connect
#-------------------------------------------
find_package(raylib 3.0 QUIET) # Let CMake search for a raylib-config.cmake

# You could change the QUIET above to REQUIRED and remove this if() clause
# This part downloads raylib and builds it if it's not installed on your system
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)

  FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/master.tar.gz
  )

  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)

    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples

    # build raylib
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})

  endif()

endif()


# Main path
#---------------------------------------------------

file(GLOB_RECURSE SRC_GAMEMODULE "src/gameModule/*.cpp" "src/gameModule/*.h")
file(GLOB_RECURSE SRC_ENGINEMODULE "src/engineModule/*.cpp" "src/engineModule/*.h")


add_executable(${This} ${SRC_GAMEMODULE} ${SRC_ENGINEMODULE})
source_group("gameModule" FILES ${SRC_GAMEMODULE})
source_group("engineModule" FILES ${SRC_ENGINEMODULE})


target_link_libraries(${This} raylib)
target_include_directories(${This} PUBLIC src)
target_compile_definitions(${This} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")
