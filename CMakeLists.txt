cmake_minimum_required(VERSION 3.24)
project(trion_engine CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

# ---- Collect sources (cpp + h) ----
file(GLOB_RECURSE ENGINE_CPP CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)
file(GLOB_RECURSE ENGINE_H CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.h"
    "${CMAKE_SOURCE_DIR}/src/*.hpp"
)

add_executable(trion_engine
    ${ENGINE_CPP}
    ${ENGINE_H}  # headers are optional for build, but great for VS filters
)

# So you can do: #include "Core/Application.h"
target_include_directories(trion_engine PRIVATE
    "${CMAKE_SOURCE_DIR}/src"
)

target_link_libraries(trion_engine PRIVATE glfw glad::glad)

# ---- Visual Studio niceties ----
if (MSVC)
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT trion_engine)
  set_target_properties(trion_engine PROPERTIES
      VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
  )
endif()

# ---- Visual Studio Filters (Solution Explorer folder view) ----
# This makes VS show the same folder structure under "Source Files" / "Header Files"
source_group(TREE "${CMAKE_SOURCE_DIR}/src" PREFIX "Source Files" FILES ${ENGINE_CPP})
source_group(TREE "${CMAKE_SOURCE_DIR}/src" PREFIX "Header Files" FILES ${ENGINE_H})
