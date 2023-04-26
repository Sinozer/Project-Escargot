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
	public:
		~AssetManager() {}
		
		static AssetManager* GetInstance();
		static void DestroyInstance();

		sf::Texture& LoadTexture(std::string name, std::string fileName, sf::IntRect area = sf::IntRect());
		sf::Texture& GetTexture(std::string name);
		bool TextureExists(std::string name);

		sf::Font& LoadFont(std::string name, std::string fileName);
		sf::Font& GetFont(std::string name);
		bool FontExists(std::string name);
	};
}