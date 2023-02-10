#include "stdafx.h"

namespace Snail
{
	Map::Map(GameDataRef data, std::string filepath) : m_data(data)
	{
		m_filepath = filepath;
		m_Init();
	}

	Map::~Map()
	{
	}

	std::vector<PhysicBodyRef> Map::GetPhysicBodyRefs()
	{
		return m_physicBodyRefs;
	}

	void Map::m_Init()
	{
		m_InitTiledFile();
		m_InitLayers();
	}

	void Map::m_InitTiledFile()
	{
		std::ifstream f(m_filepath);
		nlohmann::json data = nlohmann::json::parse(f);

		data.at("compressionlevel").get_to(m_tiledFile.compressionLevel);
		data.at("height").get_to(m_tiledFile.height);
		data.at("infinite").get_to(m_tiledFile.infinite);

		for (auto& layer : data.at("layers"))
		{
			LayerStruct layerStruct;
			layer.at("data").get_to(layerStruct.data);
			layer.at("height").get_to(layerStruct.height);
			layer.at("name").get_to(layerStruct.name);
			layer.at("opacity").get_to(layerStruct.opacity);
			layer.at("type").get_to(layerStruct.type);
			layer.at("visible").get_to(layerStruct.visible);
			layer.at("width").get_to(layerStruct.width);
			layer.at("x").get_to(layerStruct.x);
			layer.at("y").get_to(layerStruct.y);

			m_tiledFile.layers.push_back(layerStruct);
		}

		data.at("nextlayerid").get_to(m_tiledFile.nextLayerId);
		data.at("nextobjectid").get_to(m_tiledFile.nextObjectId);
		data.at("orientation").get_to(m_tiledFile.orientation);
		data.at("renderorder").get_to(m_tiledFile.renderOrder);
		data.at("tiledversion").get_to(m_tiledFile.tiledVersion);
		data.at("tileheight").get_to(m_tiledFile.tileHeight);

		for (auto& tileSet : data.at("tilesets"))
		{
			TileSetStruct tileSetStruct;
			tileSet.at("firstgid").get_to(tileSetStruct.firstGid);
			tileSet.at("source").get_to(tileSetStruct.source);

			m_tiledFile.tileSets.push_back(tileSetStruct);
		}

		data.at("tilewidth").get_to(m_tiledFile.tileWidth);
		data.at("type").get_to(m_tiledFile.type);
		data.at("version").get_to(m_tiledFile.version);
		data.at("width").get_to(m_tiledFile.width);
	}

	void Map::m_InitLayers()
	{
		for (auto& layer : m_tiledFile.layers)
		{
			if (layer.name == "background")
			{
				for (int i = 0; i < layer.data.size(); i++)
				{
					m_data->assetManager.LoadTexture("MAP_BACKGROUND_SHEET", "Resources/Textures/Map/sky_.png");
					if (layer.data.at(i) != 0)
					{
						std::string name = "MAP_BACKGROUND_";
						name.append(std::to_string(layer.data.at(i)));

						int posX = ((layer.data.at(i) - 1) * m_tiledFile.tileWidth) % m_data->assetManager.GetTexture("MAP_BACKGROUND_SHEET").getSize().x;
						int posY = (std::floor((layer.data.at(i) - 1) * m_tiledFile.tileHeight) / m_data->assetManager.GetTexture("MAP_BACKGROUND_SHEET").getSize().x) * m_tiledFile.tileHeight - posX / m_tiledFile.tileWidth - 1;

						m_data->assetManager.LoadTexture(name, "Resources/Textures/Map/sky_.png",
							sf::IntRect(sf::Vector2i(posX, posY), sf::Vector2i(m_tiledFile.tileWidth, m_tiledFile.tileHeight)));

						// Despite, show parallax
						/*m_physicBodyRefs.push_back(PhysicBodyRef(PhysicBody::CreateBoxBody(
							sf::Vector2f(m_tiledFile.tileWidth, m_tiledFile.tileHeight), sf::Vector2f((i % layer.width) * m_tiledFile.tileWidth, (i / layer.width) * m_tiledFile.tileHeight), 0.f, true,
							m_data->assetManager.GetTexture(name), false, false
						)));*/
					}
				}
			}
			else if (layer.name == "midground")
			{
				m_data->assetManager.LoadTexture("MAP_MIDGROUND_SHEET", "Resources/Textures/Map/summer_.png");
				for (int i = 0; i < layer.data.size(); i++)
				{
					if (layer.data.at(i) != 0)
					{
						std::string name = "MAP_MIDGROUND_";
						name.append(std::to_string(layer.data.at(i)));

						int posX = ((layer.data.at(i) - 29) * m_tiledFile.tileWidth) % m_data->assetManager.GetTexture("MAP_MIDGROUND_SHEET").getSize().x;
						int posY = (std::floor((layer.data.at(i) - 29) * m_tiledFile.tileHeight) / m_data->assetManager.GetTexture("MAP_MIDGROUND_SHEET").getSize().x) * m_tiledFile.tileHeight - posX / m_tiledFile.tileWidth - 1;

						m_data->assetManager.LoadTexture(name, "Resources/Textures/Map/summer_.png",
							sf::IntRect(sf::Vector2i(posX, posY), sf::Vector2i(m_tiledFile.tileWidth, m_tiledFile.tileHeight)));

						m_physicBodyRefs.push_back(PhysicBodyRef(PhysicBody::CreateBoxBody(
							sf::Vector2f(m_tiledFile.tileWidth, m_tiledFile.tileHeight), sf::Vector2f((i % layer.width) * m_tiledFile.tileWidth, (i / layer.width) * m_tiledFile.tileHeight), 0.f, true,
							m_data->assetManager.GetTexture(name), true, false
						)));
					}
				}
			}
			else if (layer.name == "object")
			{
				m_data->assetManager.LoadTexture("MAP_OBJECT_SHEET", "Resources/Textures/Map/staticObjects_.png");
				for (int i = 0; i < layer.data.size(); i++)
				{
					if (layer.data.at(i) != 0)
					{
						std::string name = "MAP_OBJECT_";
						name.append(std::to_string(layer.data.at(i)));

						int posX = ((layer.data.at(i) - 309) * m_tiledFile.tileWidth) % m_data->assetManager.GetTexture("MAP_OBJECT_SHEET").getSize().x;
						int posY = (std::floor((layer.data.at(i) - 309) * m_tiledFile.tileHeight) / m_data->assetManager.GetTexture("MAP_OBJECT_SHEET").getSize().x) * m_tiledFile.tileHeight - (posX / m_tiledFile.tileWidth - 1);

						m_data->assetManager.LoadTexture(name, "Resources/Textures/Map/staticObjects_.png",
							sf::IntRect(sf::Vector2i(posX, posY), sf::Vector2i(m_tiledFile.tileWidth, m_tiledFile.tileHeight)));

						m_physicBodyRefs.push_back(PhysicBodyRef(PhysicBody::CreateBoxBody(
							sf::Vector2f(m_tiledFile.tileWidth, m_tiledFile.tileHeight), sf::Vector2f((i % layer.width) * m_tiledFile.tileWidth, (i / layer.width) * m_tiledFile.tileHeight), 0.5f, false,
							m_data->assetManager.GetTexture(name), true, true
						)));
					}
				}
			}
		}
	}

	void Map::Update()
	{
	}

	void Map::Draw()
	{
	}
}