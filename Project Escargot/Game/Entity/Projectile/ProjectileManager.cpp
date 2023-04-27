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

		temp->Shoot(startingPoint);
	}

	void ProjectileManager::Update()
	{
		for (int i = m_projectiles.size() - 1; i >= 0; i--)
		{
			if (m_projectiles[i]->IsDeleted)
			{
				m_projectiles.erase(m_projectiles.end() - i);
				m_projectiles[i]->Destroy();
				delete m_projectiles[i];
				continue;
			}
		}
	}

	void ProjectileManager::Draw()
	{
		for (auto& i : m_projectiles)
			i->Draw();
	}
}
