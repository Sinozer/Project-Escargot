#include "stdafx.h"

namespace Snail
{
	Enemy::Enemy(GameDataRef data, Player& target) : m_target(target)
	{
		m_data = data;

		m_speed = 1.2f * PHYSIC_SCALE;
		m_jumpHeight = 1.2f * PHYSIC_SCALE;
		m_clampVelocity = { m_speed, m_jumpHeight };
		m_attackRange = 0;
		m_isMelee = true;
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
			if (m_IsAttackRange(m_isMelee))
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
		float stockPosX = m_physicBodyRef->GetPosition().x;

		switch (m_direction)
		{
		case LEFT:
			if (m_target.GetPhysicBodyRef()->GetPosition().x < m_physicBodyRef->GetPosition().x - 40)
				m_physicBodyRef->AddVelocity({ -m_speed, 0 }, m_clampVelocity);
			//Jump if progress isn't made
			if (m_physicBodyRef->GetPosition().x > stockPosX - 2.0f && m_physicBodyRef->m_IsOnGround)
			{
				m_physicBodyRef->m_IsOnGround = false;
				m_physicBodyRef->m_velocity.y = -sqrtf(2.0f * GAME_GRAVITY * m_jumpHeight);
				std::cout << "Jump";
			}
			break;
		case RIGHT:
			if (m_target.GetPhysicBodyRef()->GetPosition().x > m_physicBodyRef->GetPosition().x + 40)
				m_physicBodyRef->AddVelocity({ m_speed, 0 }, m_clampVelocity);
			//Jump if progress isn't made
			if (m_physicBodyRef->GetPosition().x < stockPosX + 2.0f && m_physicBodyRef->m_IsOnGround)
			{
				m_physicBodyRef->m_IsOnGround = false;
				m_physicBodyRef->m_velocity.y = -sqrtf(2.0f * GAME_GRAVITY * m_jumpHeight);
				std::cout << "Jump";
			}
			break;
		default:
			break;
		}
	}

	bool Enemy::m_IsPlayerInRange()
	{
		if (m_physicBodyRef->GetPosition().y - 80 < m_target.GetPhysicBodyRef()->GetPosition().y && m_target.GetPhysicBodyRef()->GetPosition().y < m_physicBodyRef->GetPosition().y + 20)
		{
			std::cout << "Player Y axis in range \n";

			if (m_physicBodyRef->GetPosition().x < m_target.GetPhysicBodyRef()->GetPosition().x && m_target.GetPhysicBodyRef()->GetPosition().x < m_physicBodyRef->GetPosition().x + 120)
			{
				return true;
			}
			else if (m_physicBodyRef->GetPosition().x - 120 < m_target.GetPhysicBodyRef()->GetPosition().x && m_target.GetPhysicBodyRef()->GetPosition().x < m_physicBodyRef->GetPosition().x)
			{
				return true;
			}
		}
		return false;
	}

	bool Enemy::m_IsAttackRange(bool isMelee)
	{

		if (isMelee && m_attackRange != 40.0f)
		{
			m_attackRange = 40.0f;
		}
		else if (!isMelee && m_attackRange != 80.0f)
		{
			m_attackRange = 80.0f;
		}

		if (m_physicBodyRef->GetPosition().x < m_target.GetPhysicBodyRef()->GetPosition().x && m_target.GetPhysicBodyRef()->GetPosition().x < m_physicBodyRef->GetPosition().x + m_attackRange)
		{
			return true;
		}
		else if (m_physicBodyRef->GetPosition().x - m_attackRange < m_target.GetPhysicBodyRef()->GetPosition().x && m_target.GetPhysicBodyRef()->GetPosition().x < m_physicBodyRef->GetPosition().x)
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