#include "stdafx.h"
#include "Map.h"
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
				m_InitLayer(layer, "MAP_BACKGROUND", "Resources/Textures/Map/Rocky Roads/Deco/background.png", true, false, false);
			}
			else if (layer.name == "midground")
			{
				m_InitLayer(layer, "MAP_MIDGROUND", "Resources/Textures/Map/Rocky Roads/Tilesets/foreground.png", true, true, false);
			}
			else if (layer.name == "object")
			{
				m_InitLayer(layer, "MAP_OBJECT", "Resources/Textures/Map/Rocky Roads/Objects/objects.png", false, true, true);
			}
		}
	}

	void Map::m_InitLayer(LayerStruct& layer, std::string sheetName, std::string sheetPath, bool isStatic, bool canCollide, bool canGravitate)
	{
		std::string textureName = m_GetTextureSheetName(sheetName);

		AssetManager::GetInstance()->LoadTexture(textureName, sheetPath);
		for (size_t i = 0; i < layer.data.size(); i++)
		{
			if (layer.data.at(i) <= 0) continue;

			int id = layer.data.at(i);

			std::string name = m_GetTextureName(sheetName, id);

			if (!AssetManager::GetInstance()->TextureExists(name))
			{
				m_CheckForTileSetAndLoadTexture(id, sheetName, sheetPath);
			}

			PhysicBody* temp = PhysicBody::CreateBoxBody(
				sf::Vector2f((float)(i % layer.width) * (float)m_tiledFile.tileWidth, (float)(i / layer.width) * (float)m_tiledFile.tileHeight), 0.5f, isStatic,
				AssetManager::GetInstance()->GetTexture(name), canCollide, canGravitate
			);

			if (canCollide)
				if (isStatic)
				{
					temp->Masks = MASK_MAP;
					temp->CollideMasks = MASK_MAP;
				}
				else
				{
					temp->Masks = MASK_MAP_OBJECT;
					temp->CollideMasks = MASK_MAP | MASK_MAP_OBJECT;
				}

			PhysicBodyManager::GetInstance()->AddPhysicBody(std::to_string(i), PhysicBodyRef(temp));
		}
	}

	void Map::m_CheckForTileSetAndLoadTexture(int id, std::string sheetName, std::string sheetPath)
	{
		std::string textureName = m_GetTextureSheetName(sheetName);

		std::string name = m_GetTextureName(sheetName, id);

		for (size_t j = m_tiledFile.tileSets.size() - 1; j >= 0; j--)
		{
			if (id < m_tiledFile.tileSets.at(j).firstGid) continue;

			id -= m_tiledFile.tileSets.at(j).firstGid;
			break;
		}

		int posX = id * m_tiledFile.tileWidth % AssetManager::GetInstance()->GetTexture(textureName).getSize().x;
		int posY = id / (AssetManager::GetInstance()->GetTexture(textureName).getSize().x / m_tiledFile.tileWidth) * m_tiledFile.tileHeight;

		AssetManager::GetInstance()->LoadTexture(name, sheetPath,
			sf::IntRect(sf::Vector2i(posX, posY), sf::Vector2i(m_tiledFile.tileWidth, m_tiledFile.tileHeight)));
	}

	std::string Map::m_GetTextureSheetName(std::string sheetName)
	{
		return sheetName.append("_SHEET");
	}

	std::string Map::m_GetTextureName(std::string sheetName, int id)
	{
		return sheetName.append("_").append(std::to_string(id));
	}

	void Map::Update()
	{
	}

	void Map::Draw()
	{
	}
}