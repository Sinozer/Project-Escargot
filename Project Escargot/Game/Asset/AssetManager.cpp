#include "stdafx.h"

namespace Snail
{
	sf::Texture& AssetManager::LoadTexture(std::string name, std::string fileName, sf::IntRect area)
	{
		if (!TextureExists(name))
		{
			sf::Texture texture;
			if (texture.loadFromFile(fileName, area))
				m_textures[name] = texture;
		}
		return GetTexture(name);
	}

	sf::Texture& AssetManager::GetTexture(std::string name)
	{
		return m_textures.at(name);
	}

	bool AssetManager::TextureExists(std::string name)
	{
		return m_textures.find(name) != m_textures.end();
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
	bool AssetManager::FontExists(std::string name)
	{
		return m_fonts.find(name) != m_fonts.end();
	}
}