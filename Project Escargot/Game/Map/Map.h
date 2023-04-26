#pragma once
#include "Game/GameData.h"
#include "Game/Physic/PhysicBodyManager.h"
namespace Snail
{
	struct LayerStruct
	{
		std::vector<int> data;
		int height;
		std::string name;
		int opacity;
		std::string type;
		bool visible;
		int width;
		int x;
		int y;
	};
	
	struct TileSetStruct
	{
		int firstGid;
		std::string source;
	};

	struct TiledFileStruct
	{
		int compressionLevel;
		int height;
		bool infinite;
		std::vector<LayerStruct> layers;
		int nextLayerId;
		int nextObjectId;
		std::string orientation;
		std::string renderOrder;
		std::string tiledVersion;
		int tileHeight;
		std::vector<TileSetStruct> tileSets;
		int tileWidth;
		std::string type;
		std::string version;
		int width;
	};

	class Map
	{
	private:
		GameDataRef m_data;

		std::string m_filepath;

		TiledFileStruct m_tiledFile;

		std::vector<PhysicBodyRef> m_physicBodyRefs;

		void m_Init();
		void m_InitTiledFile();
		void m_InitLayers();
		void m_InitLayer(LayerStruct& layer, std::string sheetName, std::string sheetPath, bool isStatic, bool canCollide, bool canGravitate);
		void m_CheckForTileSetAndLoadTexture(int id, std::string sheetName, std::string sheetPath);

		std::string m_GetTextureSheetName(std::string sheetName);
		std::string m_GetTextureName(std::string sheetName, int id);
	public:
		Map(GameDataRef data, std::string filepath);
		~Map();

		std::vector<PhysicBodyRef> GetPhysicBodyRefs();

		void Update();
		void Draw();
	};
}