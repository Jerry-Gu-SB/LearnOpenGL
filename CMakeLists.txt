cmake_minimum_required(VERSION 3.20)
project(OpenGLLearning CXX)

set(CMAKE_CXX_STANDARD 17)

# 1. Find GLFW and system OpenGL
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# 2. Add the local GLAD include directory so the compiler finds <glad/glad.h>
include_directories(${PROJECT_SOURCE_DIR}/include)

# 3. Add glad.c to the executable so it compiles alongside main.cpp
add_executable(OpenGLLearning
        main.cpp
        glad.c
)

# 4. Link the required libraries (we use the standard dl library for GLAD loader mechanics)
target_link_libraries(OpenGLLearning
        PRIVATE
        OpenGL::GL
        glfw
        ${CMAKE_DL_LIBS}
)
