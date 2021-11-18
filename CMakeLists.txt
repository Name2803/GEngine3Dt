cmake_minimum_required(VERSION 3.13 FATAL_ERROR)


set(PROJECT_NAME Hi_core)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} 
	src/main.cpp
	render/render.h
	render/render.cpp
	mat/shader001.fs
	mat/shader001.vs
	mat/shader002.fs
	mat/shader002.vs
	mat/shader003.fs
	mat/shader003.vs
	mat/shader004.fs
	mat/shader004.vs
	texture/wall.jpg
	texture/wall001.jpg
	texture/container.jpg
	texture/stone.png
	texture/Untitled.png
	texture/2.jpg
	texture/Cd9J.gif
	resources/stb_image.h
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