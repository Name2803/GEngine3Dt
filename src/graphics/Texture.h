#pragma once

class Texture {
public:
	unsigned int id;
	int height;
	int width;
	int nrChannels;

	Texture(const char* texturePath);

	Texture() = delete;
	//Texture(Texture) = delete;

};