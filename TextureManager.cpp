#include "TextureManager.h"
#include <cassert>

void TextureManager::LoadTexture(const std::string & textureName, const std::string & filename)
{
	sf::Texture texture;
	texture.loadFromFile(filename);

	textures[textureName] = texture;
}

void TextureManager::LoadFont(const std::string & fontName, const std::string & filename)
{
	sf::Font font;
	font.loadFromFile(filename);

	fonts[fontName] = font;
}

sf::Texture & TextureManager::GetTexture(const std::string & textureName)
{
	return textures[textureName];
}

sf::Font & TextureManager::GetFont(const std::string & fontName)
{
	return fonts[fontName];
}

TextureManager::TextureManager()
{
	assert(!initialized);
	initialized = false;
}

bool TextureManager::initialized = false;