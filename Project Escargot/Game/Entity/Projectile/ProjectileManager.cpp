#include "stdafx.h"

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
		/*Init();*/
	}

	ProjectileManager::~ProjectileManager()
	{
	}

	void ProjectileManager::FireBullet(Projectile &type)
	{	

	}

	void ProjectileManager::Init(PhysicBodyManager& pbm)
	{
		m_InitPhysicBody(pbm);
	}

	void ProjectileManager::m_InitPhysicBody(PhysicBodyManager& pbm)
	{

	}

	void ProjectileManager::Update(float dt)
	{

	}

	void ProjectileManager::Draw()
	{
	}
}
