#include "stdafx.h"
#include "BulletManager.h"

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
	BulletManager::BulletManager(GameDataRef data, sf::Vector2f shooterCoord, sf::Vector2f mousePositon)
	{
		Init();
	}

	BulletManager::~BulletManager()
	{
	}

	void BulletManager::Init(PhysicBodyManager& pbm)
	{
		m_InitPhysicBody(pbm);
	}

	void BulletManager::m_InitPhysicBody(PhysicBodyManager& pbm)
	{

	}

	void BulletManager::Update(float dt)
	{

	}

	void BulletManager::Draw()
	{
	}
}
