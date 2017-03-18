#pragma once
#include <SFML\Graphics.hpp>
#include <map>

class TextureManager
{
public:
	void LoadTexture(const std::string& textureName, const std::string& filename);
	void LoadFont(const std::string& fontName, const std::string& filename);
	
	sf::Texture& GetTexture(const std::string& textureName);
	sf::Font& GetFont(const std::string& fontName);

	TextureManager();

private:
	std::map<std::string, sf::Texture> textures;
	std::map<std::string, sf::Font> fonts;

	// Makes sure only one instance of this class is created
	static bool initialized;
};

