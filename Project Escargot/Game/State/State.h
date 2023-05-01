#pragma once
#include "Game/GameData.h"
#include "Game/Input/InputManager.h"
#include "Game/UI/UIManager.h"
namespace Snail
{
	/**
	 * \brief Template state class.
	 */
	class State
	{
	protected:
		static unsigned int m_count;
		void m_SetID();
		
		State() { m_SetID(); }
	protected:
		sf::Sprite m_background;
		sf::View m_view;

		UIManager m_uiManager;

		virtual void m_InitBackground() = 0;
		virtual void m_InitView() = 0;
		virtual void m_InitUIManager() = 0;

		virtual void m_UpdateView() = 0;
		virtual void m_UpdateUIManager() = 0;

		virtual void m_DrawUIManager() = 0;
	public:
		unsigned int ID = 0;

		virtual void Init() = 0;

		virtual void HandleInput() = 0;

		virtual void Update() = 0;

		virtual void Draw() = 0;
		virtual void DrawUI() = 0;

		virtual void End() = 0;
	};
}