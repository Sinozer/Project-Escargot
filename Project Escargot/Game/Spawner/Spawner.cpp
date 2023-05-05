#include "stdafx.h"
#include "Spawner.h"
#include "SpawnerManager.h"

namespace Snail 
{
	unsigned int Spawner::m_count = 0;

	Spawner::Spawner()
	{
	}

	void Spawner::Init(sf::Vector2f position)
	{
		m_InitPhysicBody(position);
	}

	//textures are to be changed later or removed if spawner is meant to be invisible
	void Spawner::m_InitPhysicBody(sf::Vector2f position)
	{
		m_physicBodyRef = PhysicBodyRef(PhysicBody::CreateBoxBody(
			sf::Vector2f(16.f, 16.f), position, 0.f, true, false, false
		));

		m_physicBodyRef->Scale(sf::Vector2f(0.5f, 0.5f));

		PhysicBodyManager::GetInstance()->AddPhysicBody("SPAWNER_" + std::to_string(m_count), m_physicBodyRef);
	
		m_count++;
	}

	void Spawner::Spawn()
	{
		Ready = false;

		Enemy* temp = new Enemy();

		temp->Init(m_physicBodyRef->GetPosition());

		m_enemyList.push_back(temp);
	}

	void Spawner::Spawn(sf::Vector2f position)
	{
		Ready = false;
		
		Enemy* temp = new Enemy();

		temp->Init(position);

		m_enemyList.push_back(temp);
	}

	void Spawner::Update()
	{
		std::vector<Enemy*> temp;

		for (int i = (int)m_enemyList.size() - 1; i >= 0; i--)
		{
			if (m_enemyList[i]->IsDeleted)
			{
				temp.push_back(m_enemyList[i]);
				continue;
			}

			m_enemyList[i]->Update();
		}

		for (auto& p : temp)
		{
			p->Destroy();
			delete p;
			std::vector<Enemy*>::iterator toDelete = std::find(m_enemyList.begin(), m_enemyList.end(), p);

			if (toDelete != m_enemyList.end())
				m_enemyList.erase(toDelete);
		}



		//for (Enemy* enemy : m_enemyList)
		//{
		//	enemy->Update();
		//	//if (enemy->IsDeleted)
		//}
		
		if (!Ready && m_enemyList.size() <= 0) Ready = true;
	}
}

