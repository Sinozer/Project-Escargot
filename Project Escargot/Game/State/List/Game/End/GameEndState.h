#pragma once
namespace Snail
{
	class GameEndState : public State
	{
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
		GameEndState(GameDataRef data);
		~GameEndState() {}

		void Init();
		void HandleInput();
		void Update();
		void Draw();
		void DrawUI();
		void End();
	};
}