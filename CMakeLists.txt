cmake_minimum_required(VERSION 3.20)
project(OpenGLWindow C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
include(ExternalProject)
find_package(Python3 REQUIRED COMPONENTS Interpreter)

# --------------------
# GLFW as submodule
# --------------------
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
add_subdirectory(external/glfw)

# --------------------
# GLM as submodule
# --------------------
add_subdirectory(external/glm)

# --------------------
# GLAD auto-generation
# --------------------
set(GLAD_OUT_DIR ${CMAKE_BINARY_DIR}/glad)
file(MAKE_DIRECTORY ${GLAD_OUT_DIR})

ExternalProject_Add(glad_gen
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/external/glad
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${Python3_EXECUTABLE} -m glad
                  --generator=c
                  --out-path=${GLAD_OUT_DIR}
                  --api=gl=3.3
    INSTALL_COMMAND ""
    BUILD_BYPRODUCTS
        ${GLAD_OUT_DIR}/src/glad.c
        ${GLAD_OUT_DIR}/include/glad/glad.h
)

add_library(glad ${GLAD_OUT_DIR}/src/glad.c)
add_dependencies(glad glad_gen)
target_include_directories(glad PUBLIC ${GLAD_OUT_DIR}/include)

# --------------------
# Main app
# --------------------
# Collect all .cpp files in src/
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp)

add_executable(Connect4 ${SRC_FILES})
target_compile_definitions(Connect4 PRIVATE GLFW_INCLUDE_NONE)

target_link_libraries(Connect4 PRIVATE glfw glad glm::glm opengl32)

# --------------------
# Copy GLFW DLL automatically
# --------------------
add_custom_command(TARGET Connect4 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:glfw>
        $<TARGET_FILE_DIR:Connect4>
)
