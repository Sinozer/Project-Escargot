#include "stdafx.h"
#include "Game/Game.h"

int main()
{
	Snail::Game game(WINDOW_SCREEN_WIDTH, WINDOW_SCREEN_HEIGHT, "Project Escargot");


#if DEBUG || DEBUG_LEAKS
	std::cout << "Press enter to continue..." << std::endl;
	std::cin.get();
#endif // DEBUG || DEBUG_LEAKS

	return 0;
}