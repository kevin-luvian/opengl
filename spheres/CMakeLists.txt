cmake_minimum_required(VERSION 3.0.0)
project(basic VERSION 0.1.0)

include(CTest)
enable_testing()

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
set(PROJECT_DIRECTORY src/)
set(LIB_DIRECTORY lib/)

set(SOURCE_FILES
    src/main.cpp
    src/glcomponent/Camera.cpp
    src/glcomponent/Screen.cpp
    src/render/Mesh.cpp
    src/render/InstancedMesh.cpp
    src/render/Shader.cpp
    src/shape/pyramid/Pyramid.cpp
    src/shape/sphere/SpherePool.cpp
    src/shape/sphere/SphereGenerator.cpp
    src/universe/SectorGenerator.cpp
    src/universe/StarPool.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_precompile_headers(${PROJECT_NAME} PRIVATE src/pch.h)

# preference for the newest OpenGL
set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

target_include_directories(${PROJECT_NAME} PUBLIC
                        ${PROJECT_DIRECTORY}
                        ${LIB_DIRECTORY}
                        ${OPENGL_INCLUDE_DIR}
                        ${GLEW_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME}
                    ${OPENGL_LIBRARIES}
                    ${GLEW_LIBRARIES}
                    glfw
                    Threads::Threads)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
