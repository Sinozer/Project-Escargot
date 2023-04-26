#include "stdafx.h"
#include "ProjectileManager.h"
#include "list/Arrow.h"
#include "Game/Entity/LivingEntity/Player/Player.h"
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
	ProjectileManager::ProjectileManager()
	{
		m_projectileRef = nullptr;
	}

	ProjectileManager::~ProjectileManager()
	{
		for (auto& i : m_projectiles)
			delete i;
	}

	void ProjectileManager::SetProjectile(Projectile* projectile)
	{
		m_projectileRef = projectile;
	}

	void ProjectileManager::Shoot(sf::Vector2f startingPoint)
	{
		Projectile* temp = m_projectileRef->Clone();

		m_projectiles.push_back(temp);

		temp->Shoot(Player::GetInstance()->GetPhysicBodyRef()->GetPosition());
		
		/*switch (m_projectileReference)
		{
		case Snail::NONE:
			break;
		case Snail::ARROW:
			Arrow* temp = new Arrow(m_data, startingPoint);
			temp->Init(m_physicBodyManager, startingPoint);
			temp->Shoot();
			m_projectiles.push_back(temp);
			
			break;
		}*/
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
