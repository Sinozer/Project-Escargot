#pragma once
namespace Snail
{
	/**
	 * \brief Template state class.
	 */
	class State
	{
	protected:
		sf::View m_view;
	public:
		virtual void Init() = 0;

		virtual void HandleInput() = 0;

		virtual void Update(float dt) = 0;

		virtual void Draw(float dt) = 0;
	};
}