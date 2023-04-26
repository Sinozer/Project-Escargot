#include "stdafx.h"
#include "Enemy.h"
namespace Snail
{
	unsigned int Enemy::Count = 0;

	Enemy::Enemy(GameDataRef data)
	{
		m_data = data;

		m_speed = 1.2f * PHYSIC_SCALE;
		m_jumpHeight = 1.2f * PHYSIC_SCALE;
		m_clampVelocity = { m_speed, m_jumpHeight };
		m_attackRange = 0;
		m_isMelee = true;
		m_forcePlayerPos = false;

		m_target = Player::GetInstance();
	}

	void Enemy::Init(sf::Vector2f position)
	{
		m_InitPhysicBody(position);
	}

	void Enemy::m_InitPhysicBody(sf::Vector2f position)
	{
		AssetManager::GetInstance()->LoadTexture("TEST_ENTITY", STATE_MAIN_ENTITY_TEST_FILEPATH);

		m_physicBodyRef = PhysicBodyRef(PhysicBody::CreateBoxBody(
			sf::Vector2f(115.f / 2.f, 161.f / 2.f), position, 0.f, false
		));

		m_physicBodyRef->Scale(sf::Vector2f(0.5f, 0.5f));

		PhysicBodyManager::GetInstance()->AddPhysicBody("ENNEMY_" + std::to_string(Count), m_physicBodyRef);

		Count++;
	}

	void Enemy::HandleInput()
	{
	}

	void Enemy::Update(float dt)
	{
		m_physicBodyRef->m_velocity.x = 0.f;

		if (m_IsPlayerInRange() || m_forcePlayerPos == true) 
		{
			if (m_IsAttackRange(m_isMelee))
			{
				std::cout << "Ennemy attacks\n";
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

		if (m_target->GetPhysicBodyRef()->GetPosition().x < m_physicBodyRef->GetPosition().x)
			m_direction = LEFT;
		else if (m_target->GetPhysicBodyRef()->GetPosition().x > m_physicBodyRef->GetPosition().x)
			m_direction = RIGHT;
	}

	void Enemy::m_UpdatePosition()
	{
		switch (m_direction)
		{
		case LEFT:
			if (m_target->GetPhysicBodyRef()->GetPosition().x < m_physicBodyRef->GetPosition().x - 40)
				m_physicBodyRef->AddVelocity({ -m_speed, 0 }, m_clampVelocity);
			
			if (previousPositionX == 0.f) break;
			//Jump if progress isn't made
			if (m_physicBodyRef->GetPosition().x > previousPositionX - 1.0f && m_physicBodyRef->m_IsOnGround)
			{
				m_physicBodyRef->m_IsOnGround = false;
				m_physicBodyRef->m_velocity.y = -sqrtf(2.0f * GAME_GRAVITY * m_jumpHeight);
			}
			break;
		case RIGHT:
			if (m_target->GetPhysicBodyRef()->GetPosition().x > m_physicBodyRef->GetPosition().x + 40)
				m_physicBodyRef->AddVelocity({ m_speed, 0 }, m_clampVelocity);

			if (previousPositionX == 0.f) break;
			//Jump if progress isn't made
			if (m_physicBodyRef->GetPosition().x < previousPositionX + 1.0f && m_physicBodyRef->m_IsOnGround)
			{
				m_physicBodyRef->m_IsOnGround = false;
				m_physicBodyRef->m_velocity.y = -sqrtf(2.0f * GAME_GRAVITY * m_jumpHeight);
			}
			break;
		default:
			break;
		}
		
		previousPositionX = m_physicBodyRef->GetPosition().x;
	}

	bool Enemy::m_IsPlayerInRange()
	{
		if (m_physicBodyRef->GetPosition().y - 80 < m_target->GetPhysicBodyRef()->GetPosition().y && m_target->GetPhysicBodyRef()->GetPosition().y < m_physicBodyRef->GetPosition().y + 20)
		{
			if (m_physicBodyRef->GetPosition().x < m_target->GetPhysicBodyRef()->GetPosition().x && m_target->GetPhysicBodyRef()->GetPosition().x < m_physicBodyRef->GetPosition().x + 120)
			{
				return true;
			}
			else if (m_physicBodyRef->GetPosition().x - 120 < m_target->GetPhysicBodyRef()->GetPosition().x && m_target->GetPhysicBodyRef()->GetPosition().x < m_physicBodyRef->GetPosition().x)
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

		if (m_physicBodyRef->GetPosition().x < m_target->GetPhysicBodyRef()->GetPosition().x && m_target->GetPhysicBodyRef()->GetPosition().x < m_physicBodyRef->GetPosition().x + m_attackRange)
		{
			return true;
		}
		else if (m_physicBodyRef->GetPosition().x - m_attackRange < m_target->GetPhysicBodyRef()->GetPosition().x && m_target->GetPhysicBodyRef()->GetPosition().x < m_physicBodyRef->GetPosition().x)
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