# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Define project name as a variable
set(PROJECT_NAME build)

# Project name and version
project(${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
# Replace 'src/main.cpp' with the actual path to your source files
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/glad.c
    src/Shader/Shader.cpp
    src/VAO/VAO.cpp
    src/VBO/VBO.cpp
    src/EBO/EBO.cpp
    src/Texture/Texture.cpp
    lib/stb_image/stb.cpp
)

# Include directories
# Replace 'include' with the path to your include directory if applicable
# target_include_directories(${PROJECT_NAME} PRIVATE include)

# Link libraries
# Uncomment and specify libraries if your project depends on any
target_link_libraries(
    ${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/libglfw3.a
    # ${CMAKE_CURRENT_SOURCE_DIR}/lib/libGLEW.a
    ${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c
)

find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)

# Enable warnings (optional)
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
endif()

# Add installation targets (optional)
# install(TARGETS ${PROJECT_NAME} DESTINATION bin)
