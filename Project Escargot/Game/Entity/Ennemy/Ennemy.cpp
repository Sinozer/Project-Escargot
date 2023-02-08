#include "stdafx.h"

namespace Snail
{
	Ennemy::Ennemy(GameDataRef data, Player& target) : m_target(target)
	{
		m_data = data;

		m_speed = 3.5f * PHYSIC_SCALE;
		m_jumpHeight = 1.2f * PHYSIC_SCALE;
		m_clampVelocity = { m_speed, m_jumpHeight };
	}

	void Ennemy::Init()
	{
		m_InitPhysicBody();
	}

	void Ennemy::m_InitPhysicBody()
	{
		m_physicBodyRef = PhysicBodyRef(PhysicBody::CreateBoxBody(
			sf::Vector2f(100.f, 100.f), sf::Vector2f(WINDOW_SCREEN_WIDTH / 3.f, WINDOW_SCREEN_HEIGHT / 3.f), 1.f, false, m_data->assetManager.GetTexture("STATE_JOIN_BACKGROUND")
		));
	}

	void Ennemy::HandleInput()
	{
	}

	void Ennemy::Update(float dt)
	{
		m_physicBodyRef->m_velocity.x = 0.f;
		if (m_target.m_physicBodyRef->GetPosition().x < m_physicBodyRef->GetPosition().x - 200)
			m_physicBodyRef->AddVelocity({ -m_speed, 0 }, m_clampVelocity);
		else if (m_target.m_physicBodyRef->GetPosition().x > m_physicBodyRef->GetPosition().x + 200)
			m_physicBodyRef->AddVelocity({ m_speed, 0 }, m_clampVelocity);
	}

	void Ennemy::Draw()
	{
	}
}
