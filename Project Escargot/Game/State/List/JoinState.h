#pragma once
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

		sf::Sprite m_background;
		sf::Uint8 m_opacity;

		bool m_isLoaded;
		
		void InitBackground();
		void InitView();

		void UpdateBackground();

		void AddMainState();
	public:
		JoinState(GameDataRef data);
		~JoinState() {}

		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
	};
}