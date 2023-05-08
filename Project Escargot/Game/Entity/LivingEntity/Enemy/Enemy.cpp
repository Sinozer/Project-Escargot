#include "stdafx.h"
#include "Enemy.h"
#include "Game/Entity/Collectables/CollectableManager.h"
namespace Snail
{
	unsigned int Enemy::Count = 0;

	Enemy::Enemy()
	{
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
		m_physicBodyRef = PhysicBodyRef(PhysicBody::CreateBoxBody(
			position, 0.f, false, AssetManager::GetInstance()->LoadTexture("DUMMY_ENTITY", STATE_GAME_DUMMY_ENTITY_FILEPATH)
		));

		m_physicBodyRef->Masks = MASK_ENEMY;
		m_physicBodyRef->CollideMasks = MASK_MAP | MASK_MAP_OBJECT | MASK_ENEMY;
		m_physicBodyRef->TriggerMasks = MASK_BULLET_PLAYER;

		m_physicBodyRef->Scale(sf::Vector2f(0.5f, 0.5f));

		Name = "ENNEMY_" + std::to_string(Count);

		PhysicBodyManager::GetInstance()->AddPhysicBody(Name, m_physicBodyRef);

		Count++;
	}

	void Enemy::HandleInput()
	{
	}

	void Enemy::Update()
	{
		m_physicBodyRef->Velocity.x = 0.f;

		if (m_IsPlayerInRange() || m_forcePlayerPos == true)
		{
			if (m_IsAttackRange(m_isMelee))
			{
				//std::cout << "Ennemy attacks\n";
			}
			else
			{
				m_ChangeDirection();
				m_UpdateSprite();
				m_UpdatePosition();
			}
		}

		m_UpdateDamageBuffer();

		// IN CASE OF MAP COLLISION BUG, HANDLING IT HERE
		if (abs(m_physicBodyRef->GetPosition().y) >= 10000.f)
		{
			m_physicBodyRef->SetPosition(sf::Vector2f(100.f, 100.f));
			m_physicBodyRef->Velocity = sf::Vector2f(0.f, 0.f);
		}

		if (!m_physicBodyRef->IsTriggered) return;
		
		if ((m_physicBodyRef->TriggeredMasks & MASK_BULLET_PLAYER) == MASK_BULLET_PLAYER)
		{
			//std::cout << m_life << std::endl;
			if (m_TakeRangeDamage(Player::GetInstance()->GetDamages()))
			{
				Player::GetInstance()->AddScore();
				
				if (m_life <= 0.f)
				{
					Player::GetInstance()->AddKill();
					CollectableManager::GetInstance()->AddCollectable(m_physicBodyRef->GetPosition());
				}
			}
		}
		
		m_physicBodyRef->IsTriggered = false;
		m_physicBodyRef->TriggeredMasks = MASK_EMPTY;
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
			if (m_physicBodyRef->GetPosition().x > previousPositionX - 1.0f && m_physicBodyRef->IsOnGround)
			{
				m_physicBodyRef->IsOnGround = false;
				m_physicBodyRef->Velocity.y = -sqrtf(2.0f * GAME_GRAVITY * m_jumpHeight);
			}
			break;
		case RIGHT:
			if (m_target->GetPhysicBodyRef()->GetPosition().x > m_physicBodyRef->GetPosition().x + 40)
				m_physicBodyRef->AddVelocity({ m_speed, 0 }, m_clampVelocity);

			if (previousPositionX == 0.f) break;
			//Jump if progress isn't made
			if (m_physicBodyRef->GetPosition().x < previousPositionX + 1.0f && m_physicBodyRef->IsOnGround)
			{
				m_physicBodyRef->IsOnGround = false;
				m_physicBodyRef->Velocity.y = -sqrtf(2.0f * GAME_GRAVITY * m_jumpHeight);
			}
			break;
		default:
			break;
		}

		previousPositionX = m_physicBodyRef->GetPosition().x;
	}

	bool Enemy::m_IsPlayerInRange()
	{
		if (m_physicBodyRef->GetPosition().y - 160.f < m_target->GetPhysicBodyRef()->GetPosition().y && m_target->GetPhysicBodyRef()->GetPosition().y < m_physicBodyRef->GetPosition().y + 60.f)
		{
			if (m_physicBodyRef->GetPosition().x < m_target->GetPhysicBodyRef()->GetPosition().x && m_target->GetPhysicBodyRef()->GetPosition().x < m_physicBodyRef->GetPosition().x + 240.f)
			{
				return true;
			}
			else if (m_physicBodyRef->GetPosition().x - 240.f < m_target->GetPhysicBodyRef()->GetPosition().x && m_target->GetPhysicBodyRef()->GetPosition().x < m_physicBodyRef->GetPosition().x)
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