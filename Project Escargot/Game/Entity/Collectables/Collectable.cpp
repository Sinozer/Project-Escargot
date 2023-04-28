#include "stdafx.h"
#include "Collectable.h"
namespace Snail {
	unsigned int m_count = 0;

	Collectable::Collectable() {
		this->m_type = Life();
		this->m_value = 15;
	}

	Collectable::~Collectable()
	{
	}

	void Collectable::Init(sf::Vector2f position)
	{
		m_InitPhysicBody(position);
	}

	void Collectable::Update( )
	{

		
	}

	void Collectable::Draw()
	{
		//m_collectablePhysicBody->Draw();
	}

	void Collectable::m_InitPhysicBody(sf::Vector2f position)
	{
		m_collectablePhysicBody = PhysicBodyRef(PhysicBody::CreateBoxBody(
			sf::Vector2f(16.f, 16.f), position, 0.f, true,true, false
		));
		PhysicBodyManager::GetInstance()->AddPhysicBody("Collectable", m_collectablePhysicBody);
	}

	void Collectable::m_CollectObject(Player livingEntity)
	{
		//livingEntity.UpdateLifeEntity(this->m_value, true);
		std::cout << "life up \n";
		
	}

	void Collectable::m_SetType(Type type)
	{
		m_type = type;
	}
	void Collectable::m_SetValue(float value)
	{
		m_value = value;
	}

	PhysicBodyRef Collectable::GetPhysicBodyRefCollectable()
	{
		return this->m_collectablePhysicBody;
	}
}