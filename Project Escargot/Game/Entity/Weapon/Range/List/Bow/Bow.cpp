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


	void Bow::Init(PhysicBodyManager &pbm)
	{
		m_InitPhysicBody(pbm);
		m_projectileManager.Init(pbm);
	}

	void Bow::m_InitPhysicBody(PhysicBodyManager &pbm)
	{
		m_physicBodyRef = PhysicBodyRef(PhysicBody::CreateBoxBody(
			sf::Vector2f(5.f, 5.f), sf::Vector2f(150, 150), 0.f, false
		));

		pbm.AddPhysicBody("BOW", m_physicBodyRef);
	}

	void Bow::Use()
	{
		//std::cout << "Bow::Use()" << "\n";
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
