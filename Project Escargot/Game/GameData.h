#pragma once
#include "Game/State/StateManager.h"
#include "Game/Asset/AssetManager.h"

namespace Snail
{
	struct GameData
	{
		sf::RenderWindow window;
		StateManager stateManager;
		AssetManager assetManager;
	};

	typedef std::shared_ptr<GameData> GameDataRef;
}
