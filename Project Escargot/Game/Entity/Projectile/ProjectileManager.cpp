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

	float ProjectileManager::GetDamages()
	{
		return m_projectileRef->GetDamages();
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
		std::vector<Projectile*> temp;

		for (int i = (int)m_projectiles.size() - 1; i >= 0; i--)
		{
			if (m_projectiles[i]->IsDeleted)
			{
				temp.push_back(m_projectiles[i]);
				continue;
			}

			m_projectiles[i]->Update();
		}

		for (auto& p : temp)
		{
			p->Destroy();
			delete p;
			std::vector<Projectile*>::iterator toDelete = std::find(m_projectiles.begin(), m_projectiles.end(), p);

			if (toDelete != m_projectiles.end())
				m_projectiles.erase(toDelete);
		}
	}

	void ProjectileManager::Draw()
	{
		for (auto& i : m_projectiles)
			i->Draw();
	}
}
