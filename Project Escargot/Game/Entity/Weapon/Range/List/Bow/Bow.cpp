#include "stdafx.h"
#include "Bow.h"


namespace Snail
{

	Bow::Bow(sf::Vector2f targetPosition)
	{
		m_projectileManager.SetProjectile(new Arrow());

		m_fireRate = .9f;
		m_fireRateDelta = 0.f;

		m_loaderAmount = 16.f;
		m_loaderAmountDelta = m_loaderAmount;

		m_loaderSize = 1.f;
		m_loaderSizeDelta = m_loaderSize;

		m_reloadTime = 1.f;
		m_reloadTimeDelta = 0.f;
	}

	Bow::~Bow()
	{
	}


	void Bow::Init(sf::Vector2f position = sf::Vector2f(150, 150))
	{
		m_InitPhysicBody(position);
	}

	void Bow::m_InitPhysicBody(sf::Vector2f position)
	{
		m_physicBodyRef = PhysicBodyRef(PhysicBody::CreateBoxBody(
			sf::Vector2f(5.f, 5.f), position, 0.f, true, false, false
		));

		PhysicBodyManager::GetInstance()->AddPhysicBody("BOW", m_physicBodyRef);
	}

	void Bow::Use()
	{
		if (m_weaponState != WeaponState::IDLE) return;

		if (!m_SetState(WeaponState::ATTACKING)) return;
		
		m_projectileManager.Shoot(m_physicBodyRef->GetPosition());
	}

	void Bow::Update(float dt)
	{
		m_UpdateState();

		m_physicBodyRef->SetPosition(InputManager::GetInstance()->GetMousePosition());
		m_projectileManager.Update(dt);
	}
	void Bow::Draw()
	{
		m_projectileManager.Draw();
	}
}
