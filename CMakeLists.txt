cmake_minimum_required(VERSION 3.13 FATAL_ERROR)


set(PROJECT_NAME Hi_core)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} 
	src/main.cpp
	src/window/window.h
	src/window/window.cpp
	src/window/events.h
	src/window/events.cpp
	src/window/camera.h
	src/window/camera.cpp
	src/graphics/shader.h
	src/graphics/shader.cpp
	src/graphics/texture.h
	src/graphics/texture.cpp
	src/graphics/marching_cube_renderer.h
	src/graphics/marching_cube_renderer.cpp

	src/mesh/mesh.h
	src/mesh/mesh.cpp
	src/marching_cubes/marching_cubes.h
	src/marching_cubes/marching_cubes.cpp
	src/marching_cubes/chunk.h
	src/marching_cubes/chunk.cpp
	src/marching_cubes/chunks.h
	src/marching_cubes/chunks.cpp
	src/helper_function/helper_function.h
	src/helper_function/helper_function.cpp
	
	src/graphics/line_batch.h
	src/graphics/line_batch.cpp
	naming_convention_for_project.txt
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


set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Hi_core)