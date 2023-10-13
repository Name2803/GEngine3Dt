#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


//предобъ€вление GLFWwindow
//class GLFWwindow;

class Window {
public:
	inline static int width;
	inline static int height;
	static GLFWwindow* window;
	static int initialize(int width, int height, const char* title);
	static void terminate();

	static void setCursorMode(int mode);
	static bool isShouldClose();
	static void setShouldClose(bool flag);
	static void swapBuffers();

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	int getWinWidth() { return width; }
	int getWinHeight() { return height; }
};