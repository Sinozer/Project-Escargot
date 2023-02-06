#include "stdafx.h"
#include "BulletManager.h"


namespace Snail
{
	BulletManager::BulletManager(GameDataRef data, sf::Vector2f shooterCoord, int dir)
	{
		this->m_data = data;
		this->m_speed = 1000.f;
		this->m_shooterCoord = shooterCoord;
		this->m_playerDir = dir;
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
		if (m_playerDir == LEFT)
		{
			m_physicBodyRef = PhysicBodyRef(PhysicBody::CreateBoxBody(
				sf::Vector2f(20.f, 10.f), sf::Vector2f(m_shooterCoord.x - 100, m_shooterCoord.y), 1.f, false,
				m_data->assetManager.GetTexture("STATE_JOIN_BACKGROUND")
			));
		}
		else if (m_playerDir == RIGHT)
			m_physicBodyRef = PhysicBodyRef(PhysicBody::CreateBoxBody(
				sf::Vector2f(20.f, 10.f), sf::Vector2f(m_shooterCoord.x + 100, m_shooterCoord.y), 1.f, false,
				m_data->assetManager.GetTexture("STATE_JOIN_BACKGROUND")
			));
		fireAmmo();
	}

	void BulletManager::fireAmmo()
	{
		if (m_playerDir == LEFT)
			m_physicBodyRef->AddVelocity({ -m_speed, 0 });
		else if (m_playerDir == RIGHT)
			m_physicBodyRef->AddVelocity({ m_speed, 0 });
	}

	void BulletManager::Update(float dt)
	{

	}

	void BulletManager::Draw()
	{
	}
}
