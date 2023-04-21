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
			sf::Vector2f(5.f, 5.f), sf::Vector2f(150, 150), 0.f, true, false, false
		));

		pbm.AddPhysicBody("BOW", m_physicBodyRef);	
	}

	void Bow::Use()
	{
		std::cout << "Bow::Use()" << "\n";
		m_projectileManager.Shoot(m_physicBodyRef->GetPosition());
	}

	void Bow::HandlerPos(sf::Vector2f handler)
	{ 
		calc = sf::Vector2f(handler.x, handler.y);
		float deltaX = InputManager::GetInstance()->GetMousePosition().x - handler.x;
		float deltaY = InputManager::GetInstance()->GetMousePosition().y - handler.y;
		float normX = (handler.x/std::sqrt(std::pow(InputManager::GetInstance()->GetMousePosition().x, 2) + std::pow(handler.x, 2)))*100;
		float normY = (handler.y/std::sqrt(std::pow(InputManager::GetInstance()->GetMousePosition().y, 2) + std::pow(handler.y, 2)))*100;
		calc = sf::Vector2f(handler.x - normX, handler.y - normY);
		std::cout << "X : " << calc.x << " <> Y : " << calc.y << "\n";
		

	}

	void Bow::Update(float dt)
	{
		m_physicBodyRef->SetPosition(calc);
		m_projectileManager.Update(dt);
	}

	void Bow::Draw()
	{
		m_projectileManager.Draw();
	}
}
