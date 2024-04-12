#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>

#include <stdint.h>

class Camera;

class Helper_function {
public:
	// ---------------------------------------------------------------
	// Console programs:
	static void printCameraPositionCons(Camera& camera, float  deltiem);
	static void printObjectPosition(glm::vec4 position, int y);

	// ---------------------------------------------------------------
	// marching cubes
	static float* ver_for_mc(int& amount, uint8_t number);
};