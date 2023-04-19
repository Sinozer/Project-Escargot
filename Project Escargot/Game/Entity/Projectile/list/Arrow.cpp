#include "stdafx.h"
//#include "Arrow.h"


namespace Snail 
{
	Arrow::Arrow(GameDataRef data, sf::Vector2f shooterCoord, unsigned int id)
	{
		m_data = data;
		m_speed = 5.f * PHYSIC_SCALE;
		m_clampVelocity = { m_speed, m_jumpHeight };
		m_shooterCoord = shooterCoord;
		m_id = id;

		float angle = std::atan2f(InputManager::GetInstance(m_data->window)->GetMousePosition().y - shooterCoord.y, InputManager::GetInstance()->GetMousePosition().x - shooterCoord.x);
		m_targetPosition = { std::cos(angle), std::sin(angle) };
	}

	Arrow::~Arrow()
	{
	}


	void Arrow::Init(PhysicBodyManager& pbm, sf::Vector2f position)
	{
		m_InitPhysicBody(pbm, position);
		//Shoot();
	}

	void Arrow::m_InitPhysicBody(PhysicBodyManager& pbm, sf::Vector2f position)
	{
		m_physicBodyRef = PhysicBodyRef(PhysicBody::CreateBoxBody(
			sf::Vector2f(5.f, 2.f), sf::Vector2f(m_shooterCoord.x, m_shooterCoord.y), 0.f, false,
			false, false
		));

		pbm.AddPhysicBody("{ENTITY NAME}_ARROW_" + std::to_string(m_id), m_physicBodyRef);
	}

	void Arrow::Shoot()
	{
		m_physicBodyRef->AddVelocity({ m_speed * m_targetPosition.x, m_speed * m_targetPosition.y }, m_clampVelocity);
	}

	void Arrow::Update(float dt)
	{
		if (m_physicBodyRef)
			m_physicBodyRef->SetPosition(sf::Vector2f(-1.f, -1.f));
	}
	
	void Arrow::Draw()
	{
	}
}

