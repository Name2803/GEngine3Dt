cmake_minimum_required(VERSION 3.13 FATAL_ERROR)


set(PROJECT_NAME Hi_core)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} 
	src/main.cpp
	src/window/window.h
	src/window/window.cpp
	src/window/Events.h
	src/window/Events.cpp
	src/window/Camera.h
	src/window/Camera.cpp
	src/graphics/ShaderCl.h
	src/graphics/ShaderCl.cpp
	src/graphics/Texture.h
	src/graphics/Texture.cpp
	src/graphics/marching_cube_renderer.h
	src/graphics/marching_cube_renderer.cpp
	src/shaders/ShV1.fs
	src/shaders/ShV1.vs
	src/shaders/Shader_1.fs
	src/shaders/Shader_1.vs
	src/mesh/Mesh.h
	src/mesh/Mesh.cpp
	src/marching_cubes/marching_cubes.h
	src/marching_cubes/marching_cubes.cpp
	src/marching_cubes/chunk.h
	src/marching_cubes/chunk.cpp
	src/marching_cubes/chunks.h
	src/marching_cubes/chunks.cpp
	src/helper_function/helper_function.h
	src/helper_function/helper_function.cpp
	src/shaders/LightCubeShader_1.fs
	src/shaders/LightCubeShader_1.vs
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)


add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

add_subdirectory(external/glm)
target_link_libraries(${PROJECT_NAME} glm)