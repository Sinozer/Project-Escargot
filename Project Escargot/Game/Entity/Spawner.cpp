#include "stdafx.h"
#include "Spawner.h"

namespace Snail 
{
	Spawner::Spawner(GameDataRef data)
	{
		m_data = data;
	}

	void Spawner::Spawn(sf::Vector2f position)
	{
		////AssetManager::GetInstance()->LoadTexture("TEST_ENTITY", STATE_MAIN_ENTITY_TEST_FILEPATH);

		//m_physicBodyRef = PhysicBodyRef(PhysicBody::CreateBoxBody(
		//	sf::Vector2f(115.f / 2.f, 161.f / 2.f), position, 0.f, false
		//));

		//m_physicBodyRef->Scale(sf::Vector2f(0.5f, 0.5f));

		//PhysicBodyManager::GetInstance()->AddPhysicBody("ENNEMY_" + std::to_string(Enemy::Count), m_physicBodyRef);

		Enemy* temp = new Enemy(m_data);

		temp->Init(position);

		m_enemyList.push_back(temp);
	}

	void Spawner::Update(float dt)
	{
		for (Enemy* enemy : m_enemyList)
		{
			enemy->Update(dt);
		}
	}

	void Spawner::Init(sf::Vector2f position)
	{
		m_InitPhysicBody(position);
	}

	//textures are to be changed later or removed if spawner is meant to be invisible
	void Spawner::m_InitPhysicBody(sf::Vector2f position)
	{
		sf::Texture texture;

		m_physicBodyRef = PhysicBodyRef(PhysicBody::CreateBoxBody(
			sf::Vector2f(115.f / 2.f, 161.f / 2.f), position, 0.f, true, texture, false, false
		));

		m_physicBodyRef->Scale(sf::Vector2f(0.5f, 0.5f));

		PhysicBodyManager::GetInstance()->AddPhysicBody("SPAWNER", m_physicBodyRef);
	}
}

