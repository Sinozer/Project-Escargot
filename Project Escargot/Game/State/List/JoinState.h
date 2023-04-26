#pragma once
#include "Game/State/State.h"
namespace Snail
{
	/**
	 * \brief First state used as a splash screen.
	 */
	class JoinState : public State
	{
	private:
		GameDataRef m_data;
		
		sf::Clock m_clock;

		sf::Uint8 m_opacity;

		bool m_isLoaded;
		
		void m_InitBackground();
		void m_InitView();
		void m_InitUIManager();

		void m_UpdateBackground();
		void m_UpdateView();
		void m_UpdateUIManager(float dt);

		void m_DrawUIManager();
		void m_AddMainState();
	public:
		JoinState(GameDataRef data);
		~JoinState() {}

		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
	};
}