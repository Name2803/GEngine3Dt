cmake_minimum_required(VERSION 3.13 FATAL_ERROR)


set(PROJECT_NAME Hi_core)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} 
	src/main.cpp
	shaders/ShaderCl.h
	shaders/ShaderCl.cpp
	glslCode/1_colors.fs
	glslCode/1_colors.vs
	glslCode/1_light_cube.fs
	glslCode/1_light_cube.vs
	glslCode/vShader.txt
	glslCode/fShader.txt
	external/stb_image.h
	atomCube/atomCube.h
	atomCube/atomCube.cpp
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
