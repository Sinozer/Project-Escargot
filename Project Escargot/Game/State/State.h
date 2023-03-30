#pragma once
namespace Snail
{
	/**
	 * \brief Template state class.
	 */
	class State
	{
	protected:
		sf::Sprite m_background;
		sf::View m_view;

		UIManager m_uiManager;

		virtual void m_InitBackground() = 0;
		virtual void m_InitView() = 0;
		virtual void m_InitUIManager() = 0;

		virtual void m_UpdateView() = 0;
		virtual void m_UpdateUIManager(float dt) = 0;

		virtual void m_DrawUIManager() = 0;
	public:
		virtual void Init() = 0;

		virtual void HandleInput() = 0;

		virtual void Update(float dt) = 0;

		virtual void Draw(float dt) = 0;
	};
}