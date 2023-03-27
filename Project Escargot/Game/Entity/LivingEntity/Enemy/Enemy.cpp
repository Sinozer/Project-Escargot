#include "stdafx.h"

namespace Snail
{
	Enemy::Enemy(GameDataRef data, Player& target) : m_target(target)
	{
		m_data = data;

		m_speed = 3.5f * PHYSIC_SCALE;
		m_jumpHeight = 1.2f * PHYSIC_SCALE;
		m_clampVelocity = { m_speed, m_jumpHeight };
	}

	void Enemy::Init(PhysicBodyManager &pbm)
	{
		m_InitPhysicBody(pbm);
	}

	void Enemy::m_InitPhysicBody(PhysicBodyManager &pbm)
	{
		m_data->assetManager.LoadTexture("TEST_ENTITY", STATE_MAIN_ENTITY_TEST_FILEPATH);

		m_physicBodyRef = PhysicBodyRef(PhysicBody::CreateBoxBody(
			sf::Vector2f(115.f / 2.f, 161.f / 2.f), sf::Vector2f(0.f, 0.f), 0.f, false, m_data->assetManager.GetTexture("TEST_ENTITY")
		));

		m_physicBodyRef->Scale(sf::Vector2f(0.5f, 0.5f));

		pbm.AddPhysicBody("ENNEMY", m_physicBodyRef);
	}

	void Enemy::HandleInput()
	{
	}

	void Enemy::Update(float dt)
	{
		m_physicBodyRef->m_velocity.x = 0.f;

		if (m_IsPlayerInRange()) 
		{
			if (m_IsAttackRange())
			{
				std::cout << "Ennemy attacks";
				
			} 
			else
			{
				m_ChangeDirection();
				m_UpdateSprite();
				m_UpdatePosition();
			}
		}
	}

	void Enemy::m_ChangeDirection(Direction direction)
	{
		if (direction != NONE)
		{
			m_direction = direction;
			return;
		}

		if (m_target.GetPhysicBodyRef()->GetPosition().x < m_physicBodyRef->GetPosition().x)
			m_direction = LEFT;
		else if (m_target.GetPhysicBodyRef()->GetPosition().x > m_physicBodyRef->GetPosition().x)
			m_direction = RIGHT;
	}

	void Enemy::m_UpdatePosition()
	{
		switch (m_direction)
		{
		case LEFT:
			if (m_target.GetPhysicBodyRef()->GetPosition().x < m_physicBodyRef->GetPosition().x - 40)
				m_physicBodyRef->AddVelocity({ -m_speed, 0 }, m_clampVelocity);
			break;
		case RIGHT:
			if (m_target.GetPhysicBodyRef()->GetPosition().x > m_physicBodyRef->GetPosition().x + 40)
				m_physicBodyRef->AddVelocity({ m_speed, 0 }, m_clampVelocity);
			break;
		default:
			break;
		}
	}

	bool Enemy::m_IsPlayerInRange()
	{
		std::cout << m_target.GetPhysicBodyRef()->GetPosition().y << "\n";

		if (m_physicBodyRef->GetPosition().y - 80 < m_target.GetPhysicBodyRef()->GetPosition().y && m_target.GetPhysicBodyRef()->GetPosition().y < m_physicBodyRef->GetPosition().y + 20)
		{
			std::cout << "Player Y axis in range \n";

			if (m_physicBodyRef->GetPosition().x < m_target.GetPhysicBodyRef()->GetPosition().x && m_target.GetPhysicBodyRef()->GetPosition().x < m_physicBodyRef->GetPosition().x + 120)
			{
				std::cout << "Player aggroed right \n\n";
				return true;
			}
			else if (m_physicBodyRef->GetPosition().x - 120 < m_target.GetPhysicBodyRef()->GetPosition().x && m_target.GetPhysicBodyRef()->GetPosition().x < m_physicBodyRef->GetPosition().x)
			{
				std::cout << "Player aggroed left \n\n";
				return true;
			}
		}
		return false;
	}

	bool Enemy::m_IsAttackRange()
	{
		if (m_physicBodyRef->GetPosition().x < m_target.GetPhysicBodyRef()->GetPosition().x && m_target.GetPhysicBodyRef()->GetPosition().x < m_physicBodyRef->GetPosition().x + 20)
		{
			return true;
		}
		else if (m_physicBodyRef->GetPosition().x - 20 < m_target.GetPhysicBodyRef()->GetPosition().x && m_target.GetPhysicBodyRef()->GetPosition().x < m_physicBodyRef->GetPosition().x)
		{
			return true;
		}
		return false;
	}

	void Enemy::Draw()
	{
	}

	PhysicBodyRef Enemy::GetPhysicBodyRef()
	{
		return m_physicBodyRef;
	}
}