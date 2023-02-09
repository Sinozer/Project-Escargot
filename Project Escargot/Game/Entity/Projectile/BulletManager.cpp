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
		this->m_data = data;
		this->m_speed = 5.f * PHYSIC_SCALE;
		m_clampVelocity = { m_speed, m_jumpHeight };
		this->m_shooterCoord = shooterCoord;


		float angle = std::atan2f(mousePositon.y - shooterCoord.y, mousePositon.x - shooterCoord.x);
		m_targetPosition = { std::cos(angle), std::sin(angle) };


		Init();
	}

	BulletManager::~BulletManager()
	{
	}

	void BulletManager::Init()
	{
		m_InitPhysicBody();
	}

	void BulletManager::m_InitPhysicBody()
	{

		m_physicBodyRef = PhysicBodyRef(PhysicBody::CreateBoxBody(
			sf::Vector2f(20.f, 10.f), sf::Vector2f(m_shooterCoord.x, m_shooterCoord.y), 1.f, false,
			m_data->assetManager.GetTexture("STATE_JOIN_BACKGROUND"), false, false
		));
		fireAmmo();
	}

	void BulletManager::fireAmmo()
	{
		m_physicBodyRef->AddVelocity({ m_speed * m_targetPosition.x, m_speed * m_targetPosition.y }, m_clampVelocity);
	}

	void BulletManager::Update(float dt)
	{

	}

	void BulletManager::Draw()
	{
	}
}
