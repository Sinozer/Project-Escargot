#pragma once
#include "Game/State/State.h"
namespace Snail
{
	/**
	 * \brief First state used as a splash screen.
	 */
	class MainState : public State
	{
	private:
		static int m_id;

	private:
		GameDataRef m_data;

		bool m_isLoaded;
		
		void m_InitBackground();
		void m_InitView();
		void m_InitUIManager();
		void m_InitUITexts();
		void m_InitUIButtons();

		void m_UpdateView();
		void m_UpdateUIManager();

		void m_DrawUIManager();
	public:
		MainState(GameDataRef data);
		~MainState() {}

		void Init();
		void HandleInput();
		void Update();
		void Draw();
		void DrawUI();
		void End();
	};
}