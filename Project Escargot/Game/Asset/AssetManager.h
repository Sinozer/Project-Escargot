#pragma once
namespace Snail
{
	class AssetManager
	{
	private:
		std::map<std::string, sf::Texture> m_textures;
		std::map<std::string, sf::Font> m_fonts;
	public:
		AssetManager() {}
		~AssetManager() {}
		
		sf::Texture& LoadTexture(std::string name, std::string fileName);
		sf::Texture& GetTexture(std::string name);
		bool TextureExists(std::string name);

		sf::Font& LoadFont(std::string name, std::string fileName);
		sf::Font& GetFont(std::string name);
		bool FontExists(std::string name);
	};
}