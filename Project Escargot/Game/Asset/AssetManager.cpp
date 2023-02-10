#include "stdafx.h"

namespace Snail
{
	sf::Texture& AssetManager::LoadTexture(std::string name, std::string fileName)
	{
		if (m_textures.find(name) != m_textures.end()) return GetTexture(name);

		sf::Texture texture;

		if (texture.loadFromFile(fileName))
			return m_textures[name] = texture;
	}

	sf::Texture& AssetManager::GetTexture(std::string name)
	{
		return m_textures.at(name);
	}

	void AssetManager::LoadFont(std::string name, std::string fileName)
	{
		sf::Font font;
		if (font.loadFromFile(fileName))
			m_fonts[name] = font;
	}

	sf::Font& AssetManager::GetFont(std::string name)
	{
		return m_fonts.at(name);
	}
}