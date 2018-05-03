#include "TextureManager.h"

GLuint TextureManager::GetID(string name)
{
	return textureMap[name];
}

bool TextureManager::LoadFromFile(string filename, string name)
{
	//Creates a textureID and it loads a texture which we will bind to the ID
	GLuint textureID;
	glGenTextures(1, &textureID);

	SDL_Surface* textureData = 0;
	textureData = IMG_Load(filename.c_str());

	if (!textureData)
	{
		cout << "Error Loading Texture";
		return false;
	}

	glBindTexture(GL_TEXTURE_2D, textureID);

	unsigned char* pixels = (unsigned char*)textureData->pixels;
	unsigned int width = textureData->w;
	unsigned int height = textureData->h;
	unsigned int depth = textureData->format->BytesPerPixel;
	unsigned format((depth == 4) ? GL_RGBA : GL_RGB);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);
	glGenerateMipmap(GL_TEXTURE_2D);


	glBindTexture(GL_TEXTURE_2D, 0);

	//remove image from memory
	SDL_FreeSurface(textureData);

	textureMap[name] = textureID;

	return true;

}

void TextureManager::UnloadFromMemory()
{
	for (auto it = textureMap.begin(); it != textureMap.end(); it++)
	{
		glDeleteTextures(1, &(it->second));
	}
	textureMap.clear();
}