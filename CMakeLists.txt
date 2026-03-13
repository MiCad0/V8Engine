cmake_minimum_required(VERSION 4.1)
project(V8Engine)

set(CMAKE_CXX_STANDARD 20)

find_package(Vulkan REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(glm REQUIRED)

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/shaders"
        DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

add_executable(V8Engine main.cpp
        square.h
)

target_link_libraries(V8Engine PRIVATE
        Vulkan::Vulkan
        glfw
)