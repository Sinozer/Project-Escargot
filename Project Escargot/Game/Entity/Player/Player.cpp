#include "stdafx.h"

namespace Snail
{
	Player::Player(GameDataRef data)
	{
		m_data = data;

		m_speed = 4.f * PHYSIC_SCALE;
		m_jumpHeight = 1.5f * PHYSIC_SCALE;
		m_clamp = { m_speed, m_jumpHeight };
		bulletCount = 0;
		m_playerDir = RIGHT;
	}

	void Player::Init()
	{

		m_InitPhysicBody();
	}

	void Player::m_InitPhysicBody()
	{
		m_physicBodyRef = PhysicBodyRef(PhysicBody::CreateBoxBody(
			sf::Vector2f(100.f, 100.f), sf::Vector2f(/*WINDOW_SCREEN_WIDTH / 2.f*/200, /*WINDOW_SCREEN_HEIGHT / 2.f*/ 200), 0.f, false/*, m_data->assetManager.GetTexture("STATE_JOIN_BACKGROUND")*/
		));
	}

	void Player::HandleInput()
	{
		m_physicBodyRef->m_velocity.x = 0.f;
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) 
		{
			m_physicBodyRef->AddVelocity({-m_speed, 0}, m_clamp);
			m_playerDir = LEFT;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			m_physicBodyRef->AddVelocity({ m_speed, 0}, m_clamp);
			m_playerDir = RIGHT;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_physicBodyRef->m_IsOnGround)
		{
			m_physicBodyRef->m_IsOnGround = false;
			m_physicBodyRef->m_velocity.y = -sqrtf(2.0f * GAME_GRAVITY * m_jumpHeight);
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
		{
			bulletCount ++;

			//===================== ACTUAL CALLBACK TEST =====================
			Callback(TestCallBack);
		}
		
	}

	void Player::Update(float dt)
	{
	}

	void Player::Draw()
	{
	}
}
