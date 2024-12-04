cmake_minimum_required(VERSION 3.15)

# Project configuration
project(OcctImgui LANGUAGES CXX)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE})

# Include directories
find_package(glfw3 REQUIRED)
find_package(OpenCASCADE REQUIRED)

file(GLOB_RECURSE SOURCES
    "${CMAKE_SOURCE_DIR}/*.cpp"
    "${CMAKE_SOURCE_DIR}/*.h"
)

# Exclude CMake-generated files from the SOURCES list
list(FILTER SOURCES EXCLUDE REGEX ".*CMakeFiles.*")

# Add executable target
add_executable(OcctImgui ${SOURCES})

# Link libraries
target_link_libraries(OcctImgui
PRIVATE    TKernel TKMath TKG2d TKG3d TKGeomBase TKGeomAlgo TKBRep TKTopAlgo TKPrim TKMesh TKService TKOpenGl TKV3d
  glfw
)

target_compile_options(OcctImgui PRIVATE
    $<$<CONFIG:Debug>:-g>
    $<$<CONFIG:Release>:-O3>
)

target_link_directories(OcctImgui PRIVATE
    $<$<CONFIG:Debug>:${DEBUG_LIBS}>
    $<$<CONFIG:Release>:${RELEASE_LIBS}>
)

# Debug environment variables (for Windows)
if(WIN32)
    set(DEBUG_ENVS "path=%path%;D:/OpenCASCADE-7.7.0/opencascade-7.7.0/win64/vc14/bind")
    set(RELEASE_ENVS "path=%path%;D:/OpenCASCADE-7.7.0/opencascade-7.7.0/win64/vc14/bin")

    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set_target_properties(OcctImgui PROPERTIES VS_DEBUGGER_ENVIRONMENT "${DEBUG_ENVS}")
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
        set_target_properties(OcctImgui PROPERTIES VS_DEBUGGER_ENVIRONMENT "${RELEASE_ENVS}")
    endif()
endif()

