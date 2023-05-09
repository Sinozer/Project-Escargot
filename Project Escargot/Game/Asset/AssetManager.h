#pragma once
namespace Snail
{
	class AssetManager
	{
	private:
		// Singleton
		static AssetManager* m_instance;
		AssetManager() {}
	private:
		std::map<std::string, sf::Texture> m_textures;
		
		std::map<std::string, sf::Font> m_fonts;
		
		sf::Sound m_sound;
		std::map<std::string, sf::SoundBuffer> m_soundBuffers;
		
		sf::Music m_music;
		std::map<std::string, std::string> m_musics;
	public:
		~AssetManager() {}

		static const bool IsInstance();
		static AssetManager* GetInstance();
		static const void DestroyInstance();

		sf::Texture& LoadTexture(std::string name, std::string fileName, sf::IntRect area = sf::IntRect());
		sf::Texture& GetTexture(std::string name);
		const bool TextureExists(std::string name) const;

		sf::Font& LoadFont(std::string name, std::string fileName);
		sf::Font& GetFont(std::string name);
		const bool FontExists(std::string name) const;

		sf::SoundBuffer& LoadSoundBuffer(std::string name, std::string fileName);
		void PlaySound(const std::string name);
	private:
		sf::SoundBuffer& m_GetSoundBuffer(std::string name);
		const bool m_SoundBufferExists(std::string name) const;

	public:
		const std::string LoadMusic(std::string name, std::string fileName);
		void PlayMusic(const std::string name);
	private:
		const std::string m_GetMusic(std::string name) const;
		const bool m_MusicExists(std::string name) const;
	};
}