#include "stdafx.h"
#include "Bow.h"


namespace Snail
{

	Bow::Bow(sf::Vector2f targetPosition)
	{
		Init(targetPosition);
	}

	Bow::~Bow()
	{
	}


	void Bow::Init(sf::Vector2f targetPosition)
	{
		m_InitPhysicBody();
		float angle = std::atan2f(targetPosition.y - 150, targetPosition.x - 150);
		m_targetPosition = { std::cos(angle), std::sin(angle) };

	}

	void Bow::m_InitPhysicBody()
	{
		m_physicBodyRef = PhysicBodyRef(PhysicBody::CreateBoxBody(
			sf::Vector2f(5.f, 5.f), sf::Vector2f(150, 150), 0.f, false
		));
	}

	void Bow::Use()
	{

	}

	void Bow::Update(float dt)
	{
		m_physicBodyRef->SetPosition(m_targetPosition);
	}
	void Bow::Draw()
	{
	}
}
