#pragma once

#include <iostream>
#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../external/stb_image.h"

class Texture2D {
public:
	Texture2D();
	void Texture(const char* texture2Dpath, unsigned int &texture) ;

    Texture2D() = delete;
    Texture2D(const Texture2D&) = delete;
    Texture2D& operator=(const Texture2D&) = delete;
    Texture2D& operator=(Texture2D&& textire2d);
    Texture2D(Texture2D&& texture2d);
};