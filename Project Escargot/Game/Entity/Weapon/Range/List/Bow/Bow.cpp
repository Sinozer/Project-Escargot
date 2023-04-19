#include "stdafx.h"
#include "Bow.h"


namespace Snail
{

	Bow::Bow(sf::Vector2f targetPosition)
	{

		m_projectileManager.SetProjectile(ARROW);
	}

	Bow::~Bow()
	{
	}


	void Bow::Init(PhysicBodyManager &pbm, sf::Vector2f position = sf::Vector2f(150, 150))
	{
		m_InitPhysicBody(pbm, position);
		m_projectileManager.Init(pbm, position);
	}

	void Bow::m_InitPhysicBody(PhysicBodyManager &pbm, sf::Vector2f position)
	{
		m_physicBodyRef = PhysicBodyRef(PhysicBody::CreateBoxBody(
			sf::Vector2f(5.f, 5.f), position, 0.f, true, false, false
		));

		pbm.AddPhysicBody("BOW", m_physicBodyRef);
	}

	void Bow::Use()
	{
		std::cout << "Bow::Use()" << "\n";
		m_projectileManager.Shoot(m_physicBodyRef->GetPosition());
	}

	void Bow::Update(float dt)
	{
		m_physicBodyRef->SetPosition(InputManager::GetInstance()->GetMousePosition());
		m_projectileManager.Update(dt);
	}
	void Bow::Draw()
	{
		m_projectileManager.Draw();
	}
}
