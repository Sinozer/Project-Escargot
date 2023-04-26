#pragma once
#include "Game/State/StateManager.h"

namespace Snail
{
	struct GameData
	{
		sf::RenderWindow window;
		StateManager stateManager;
		float deltaTime;
	};

	typedef std::shared_ptr<GameData> GameDataRef;
}
