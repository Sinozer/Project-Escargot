#include "stdafx.h"
#include "AssetManager.h"

namespace Snail
{
#pragma region Singleton
	AssetManager* AssetManager::m_instance = nullptr;

	const bool AssetManager::IsInstance()
	{
		return m_instance != nullptr;
	}

	AssetManager* AssetManager::GetInstance()
	{
		if (m_instance == nullptr)
			m_instance = new AssetManager();

		return m_instance;
	}

	const void AssetManager::DestroyInstance()
	{
		delete m_instance;
		m_instance = nullptr;
	}
#pragma endregion

#pragma region Textures
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

	const bool AssetManager::TextureExists(std::string name) const
	{
		return m_textures.find(name) != m_textures.end();
	}
#pragma endregion

#pragma region Fonts
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

	const bool AssetManager::FontExists(std::string name) const
	{
		return m_fonts.find(name) != m_fonts.end();
	}
#pragma endregion

#pragma region SoundBuffers
	sf::SoundBuffer& AssetManager::LoadSoundBuffer(std::string name, std::string fileName)
	{
		if (!m_SoundBufferExists(name))
		{
			sf::SoundBuffer soundBuffer;
			if (soundBuffer.loadFromFile(fileName))
				m_soundBuffers[name] = soundBuffer;
		}
		return m_GetSoundBuffer(name);
	}

	void AssetManager::PlaySound(const std::string name)
	{
		m_sound.setVolume(50.f);
		m_sound.setBuffer(m_GetSoundBuffer(name));
		m_sound.play();
	}

	sf::SoundBuffer& AssetManager::m_GetSoundBuffer(std::string name)
	{
		return m_soundBuffers.at(name);
	}

	const bool AssetManager::m_SoundBufferExists(std::string name) const
	{
		return m_soundBuffers.find(name) != m_soundBuffers.end();
	}
#pragma endregion

#pragma region Musics
	const std::string AssetManager::LoadMusic(std::string name, std::string fileName)
	{
		if (!m_MusicExists(name))
		{
			m_musics[name] = fileName;
		}
		return m_GetMusic(name);
	}

	void AssetManager::PlayMusic(const std::string name)
	{
		m_music.setVolume(20.f);
		m_music.setLoop(true);
		m_music.openFromFile(m_GetMusic(name));
		m_music.play();
	}

	const std::string AssetManager::m_GetMusic(std::string name) const
	{
		return m_musics.at(name);
	}

	const bool AssetManager::m_MusicExists(std::string name) const
	{
		return m_musics.find(name) != m_musics.end();
	}
#pragma endregion
}