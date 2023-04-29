#include "stdafx.h"
#include "Arrow.h"
#include "Game/Entity/LivingEntity/Player/Player.h"
namespace Snail
{
	Arrow::Arrow()
	{
		m_speed = 2.f * PHYSIC_SCALE;
		m_clampVelocity = { m_speed, m_jumpHeight };
	}

	Arrow::~Arrow()
	{
	}


	void Arrow::Init(sf::Vector2f position)
	{
		m_InitPhysicBody(position);
	}

	unsigned int Arrow::m_count = 0;
	void Arrow::m_InitPhysicBody(sf::Vector2f position)
	{
		m_physicBodyRef = PhysicBodyRef(PhysicBody::CreateBoxBody(
			sf::Vector2f(5.f, 2.f), sf::Vector2f(position.x, position.y), 0.f, false,
			true, false
		));

		m_physicBodyRef->Masks = MASK_BULLET_PLAYER;
		//m_physicBodyRef->CollideMasks = MASK_ENEMY;
		m_physicBodyRef->TriggerMasks = MASK_MAP;

		m_name = "ARROW_" + std::to_string(m_count);

		PhysicBodyManager::GetInstance()->AddPhysicBody(m_name, m_physicBodyRef);
		m_count++;
	}

	Arrow* Arrow::Clone()
	{
		return new Arrow(*this);
	}

	void Arrow::Shoot(sf::Vector2f shooterCoord)
	{
		float angle = std::atan2f(shooterCoord.y - Player::GetInstance()->GetPhysicBodyRef()->GetPosition().y, shooterCoord.x - Player::GetInstance()->GetPhysicBodyRef()->GetPosition().x);
		m_targetPosition = { std::cos(angle), std::sin(angle) };

		m_InitPhysicBody(shooterCoord);

		m_physicBodyRef->AddVelocity({ m_speed * m_targetPosition.x, m_speed * m_targetPosition.y }, m_clampVelocity);
	}

	void Arrow::Update()
	{
		if (!m_physicBodyRef->IsTriggered) return;

		if ((m_physicBodyRef->TriggeredMasks & MASK_MAP) == MASK_MAP)
		{
			IsDeleted = true;
		}
		if ((m_physicBodyRef->TriggeredMasks & MASK_ENEMY) == MASK_ENEMY)
		{
			IsDeleted = true;
		}
		m_physicBodyRef->IsTriggered = false;
		m_physicBodyRef->TriggeredMasks = MASK_EMPTY;
	}

	void Arrow::Draw()
	{
	}
}

