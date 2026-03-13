cmake_minimum_required(VERSION 4.1)
project(V8Engine)

set(CMAKE_CXX_STANDARD 20)

find_package(Vulkan REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(glm REQUIRED)

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/shaders"
        DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

add_executable(V8Engine main.cpp
        rect.h
        cube.h
)

target_link_libraries(V8Engine PRIVATE
        Vulkan::Vulkan
        glfw
)

find_program(GLSLC_EXECUTABLE glslc)

if(GLSLC_EXECUTABLE)
    set(SHADER_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/shaders")
    set(SHADER_BIN_DIR "${CMAKE_CURRENT_BINARY_DIR}/shaders")
    file(MAKE_DIRECTORY ${SHADER_BIN_DIR})

    add_custom_command(
            OUTPUT ${SHADER_BIN_DIR}/vert.spv
            COMMAND ${GLSLC_EXECUTABLE} ${SHADER_SRC_DIR}/shader.vert -o ${SHADER_BIN_DIR}/vert.spv
            DEPENDS ${SHADER_SRC_DIR}/shader.vert
    )

    add_custom_command(
            OUTPUT ${SHADER_BIN_DIR}/frag.spv
            COMMAND ${GLSLC_EXECUTABLE} ${SHADER_SRC_DIR}/shader.frag -o ${SHADER_BIN_DIR}/frag.spv
            DEPENDS ${SHADER_SRC_DIR}/shader.frag
    )

    add_custom_target(CompileShaders ALL DEPENDS ${SHADER_BIN_DIR}/vert.spv ${SHADER_BIN_DIR}/frag.spv)

    add_dependencies(V8Engine CompileShaders)
else()
    message(WARNING "Unable to find glslc. Shaders will not be compiled automatically.")
endif()