#include "stdafx.h"

namespace Snail
{
	Player::Player(GameDataRef data)
	{
		m_data = data;

		m_speed = 1.25f * PHYSIC_SCALE;
		m_jumpHeight = 0.75f * PHYSIC_SCALE;
		m_clampVelocity = { m_speed, m_jumpHeight };
		bulletCount = 0;
	}

	void Player::Init()
	{

		m_InitPhysicBody();
	}

	void Player::m_InitPhysicBody()
	{
		m_physicBodyRef = PhysicBodyRef(PhysicBody::CreateBoxBody(
			sf::Vector2f(16.f, 32.f), sf::Vector2f(150, 150), 0.f, false/*, m_data->assetManager.GetTexture("STATE_JOIN_BACKGROUND")*/
		));
	}

	void Player::HandleInput()
	{
		m_physicBodyRef->m_velocity.x = 0.f;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			m_physicBodyRef->AddVelocity({ -m_speed, 0 }, m_clampVelocity);
			m_UpdateDirection(LEFT);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			m_physicBodyRef->AddVelocity({ m_speed, 0 }, m_clampVelocity);
			m_UpdateDirection(RIGHT);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_physicBodyRef->m_IsOnGround)
		{
			m_physicBodyRef->m_IsOnGround = false;
			m_physicBodyRef->m_velocity.y = -sqrtf(2.0f * GAME_GRAVITY * m_jumpHeight);
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			bulletCount++;
		}

		//if (DEBUG)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			m_physicBodyRef->SetPosition({ 150, 150 });
		}

	}

	void Player::Update(float dt)
	{
	}

	void Player::m_UpdateDirection(Direction direction)
	{
		m_direction = direction;
	}

	void Player::Draw()
	{
	}

	PhysicBodyRef Player::GetPhysicBodyRef()
	{
		return m_physicBodyRef;
	}
}
