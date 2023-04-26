#include "stdafx.h"
#include "ProjectileManager.h"
#include "list/Arrow.h"
/**
 *
 * MainState
 * Player
 *
 * WeaponManager
 * Weapon (abstraite)
 * -- Arc
 * -- Famas
 *
 * ProjectileManager
 * Projectile	: Entity
 * {
 * m_physicBody
 *
 * m_velocity
 *
 * }
 * -- Flèches
 * -- Balles
 *
 */

namespace Snail
{
	ProjectileManager::ProjectileManager(GameDataRef data, sf::Vector2f shooterCoord, sf::Vector2f mousePositon)
	{
		m_data = data;
		/*Init();*/
	}

	ProjectileManager::~ProjectileManager()
	{
		for (auto& i : m_projectiles)
			delete i;
	}

	void ProjectileManager::Init(PhysicBodyManager& pbm, sf::Vector2f position = sf::Vector2f(0,0))
	{
		m_InitPhysicBody(pbm, position);
	}

	void ProjectileManager::m_InitPhysicBody(PhysicBodyManager& pbm, sf::Vector2f position)
	{
		m_physicBodyManager = pbm;
	}

	void ProjectileManager::SetProjectile(EProjectile ref)
	{
		m_projectileReference = ref;
	}

	void ProjectileManager::Shoot(sf::Vector2f startingPoint)
	{
		switch (m_projectileReference)
		{
		case Snail::NONE:
			break;
		case Snail::ARROW:
			Arrow* temp = new Arrow(m_data, startingPoint);
			temp->Init(m_physicBodyManager, startingPoint);
			temp->Shoot();
			m_projectiles.push_back(temp);
			
			break;
		}
	}

	void ProjectileManager::Update(float dt)
	{
		for (auto& i : m_projectiles)
			i->Update(dt);
	}

	void ProjectileManager::Draw()
	{
		for (auto& i : m_projectiles)
			i->Draw();
	}
}
