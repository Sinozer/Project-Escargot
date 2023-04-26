#pragma once
#include "Game/State/StateManager.h"

namespace Snail
{
	struct GameData
	{
		sf::RenderWindow window;
		StateManager stateManager;
	};

	typedef std::shared_ptr<GameData> GameDataRef;
}
