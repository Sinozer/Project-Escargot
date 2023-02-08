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
		m_data->assetManager.LoadTexture("TEST_ENTITY", STATE_MAIN_ENTITY_TEST_FILEPATH);

		m_physicBodyRef = PhysicBodyRef(PhysicBody::CreateBoxBody(
			sf::Vector2f(115.f, 161.f), sf::Vector2f(WINDOW_SCREEN_WIDTH / 3.f, WINDOW_SCREEN_HEIGHT / 3.f), 1.f, false, m_data->assetManager.GetTexture("TEST_ENTITY")
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