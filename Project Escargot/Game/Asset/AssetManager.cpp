#include "stdafx.h"
#include "AssetManager.h"

namespace Snail
{
	AssetManager* AssetManager::m_instance = nullptr;

	AssetManager* AssetManager::GetInstance()
	{
		if (m_instance == nullptr)
			m_instance = new AssetManager();

		return m_instance;
	}

	void AssetManager::DestroyInstance()
	{
		delete m_instance;
		m_instance = nullptr;
	}
	
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

	sf::Font& AssetManager::LoadFont(std::string name, std::string fileName)
	{
		if (!FontExists(name))
		{
			sf::Font font;
			if (font.loadFromFile(fileName))
				m_fonts[name] = font;
		}
		return GetFont(name);
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