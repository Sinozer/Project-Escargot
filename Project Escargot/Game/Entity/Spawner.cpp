#include "stdafx.h"

namespace Snail 
{
	Spawner::Spawner(GameDataRef data)
	{
		m_data = data;
	}

	void Spawner::Spawn(PhysicBodyManager& pbm, Enemy enemy, sf::Vector2f position)
	{
		//m_data->assetManager.LoadTexture("TEST_ENTITY", STATE_MAIN_ENTITY_TEST_FILEPATH);

		m_physicBodyRef = PhysicBodyRef(PhysicBody::CreateBoxBody(
			sf::Vector2f(115.f / 2.f, 161.f / 2.f), position, 0.f, false
		));

		m_physicBodyRef->Scale(sf::Vector2f(0.5f, 0.5f));

		pbm.AddPhysicBody("ENNEMY2", m_physicBodyRef);
	}

	void Spawner::Init(PhysicBodyManager& pbm, sf::Vector2f position)
	{
		m_InitPhysicBody(pbm, position);
	}

	//textures are to be changed later or removed if spawner is meant to be invisible
	void Spawner::m_InitPhysicBody(PhysicBodyManager& pbm, sf::Vector2f position)
	{
		sf::Texture texture;

		m_physicBodyRef = PhysicBodyRef(PhysicBody::CreateBoxBody(
			sf::Vector2f(115.f / 2.f, 161.f / 2.f), position, 0.f, true, texture, false, false
		));

		m_physicBodyRef->Scale(sf::Vector2f(0.5f, 0.5f));

		pbm.AddPhysicBody("SPAWNER", m_physicBodyRef);
	}
}

