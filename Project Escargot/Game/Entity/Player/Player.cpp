#include "stdafx.h"

namespace Snail
{
	Player::Player(GameDataRef data)
	{
		m_data = data;

		m_speed = 100.f;
		m_jumpHeight = 150.f;
	}

	void Player::Init()
	{
		m_InitPhysicBody();
	}

	void Player::m_InitPhysicBody()
	{
		m_physicBodyRef = PhysicBodyRef(PhysicBody::CreateBoxBody(
			sf::Vector2f(100.f, 100.f), sf::Vector2f(WINDOW_SCREEN_WIDTH / 2.f, WINDOW_SCREEN_HEIGHT / 2.f), 1.f, false
		));
	}

	void Player::HandleInput()
	{
		m_physicBodyRef->m_velocity.x = 0.f;
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			m_physicBodyRef->AddVelocity({-m_speed, 0});
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			m_physicBodyRef->AddVelocity({ m_speed, 0});
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_physicBodyRef->m_IsOnGround)
		{
			m_physicBodyRef->m_IsOnGround = false;
			m_physicBodyRef->m_velocity.y = -sqrtf(2.0f * GAME_GRAVITY * m_jumpHeight);
		}
		
	}

	void Player::Update(float dt)
	{
	}

	void Player::Draw()
	{
	}
}
