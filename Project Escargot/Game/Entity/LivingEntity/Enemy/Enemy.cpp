#include "stdafx.h"

namespace Snail
{
	Enemy::Enemy(GameDataRef data, Player& target) : m_target(target)
	{
		m_data = data;

		m_speed = 3.5f * PHYSIC_SCALE;
		m_jumpHeight = 1.2f * PHYSIC_SCALE;
		m_clampVelocity = { m_speed, m_jumpHeight };
	}

	void Enemy::Init()
	{
		m_InitPhysicBody();
	}

	void Enemy::m_InitPhysicBody()
	{
		m_data->assetManager.LoadTexture("TEST_ENTITY", STATE_MAIN_ENTITY_TEST_FILEPATH);

		m_physicBodyRef = PhysicBodyRef(PhysicBody::CreateBoxBody(
			sf::Vector2f(115.f / 2.f, 161.f / 2.f), sf::Vector2f(0.f, 0.f), 0.f, false, m_data->assetManager.GetTexture("TEST_ENTITY")
		));

		m_physicBodyRef->Scale(sf::Vector2f(0.5f, 0.5f));
	}

	void Enemy::HandleInput()
	{
	}

	void Enemy::Update(float dt)
	{
		m_physicBodyRef->m_velocity.x = 0.f;
		m_ChangeDirection();
		m_UpdateSprite();
		m_UpdatePosition();
	}

	void Enemy::m_ChangeDirection(Direction direction)
	{
		if (direction != NONE)
		{
			m_direction = direction;
			return;
		}

		if (m_target.GetPhysicBodyRef()->GetPosition().x < m_physicBodyRef->GetPosition().x)
			m_direction = LEFT;
		else if (m_target.GetPhysicBodyRef()->GetPosition().x > m_physicBodyRef->GetPosition().x)
			m_direction = RIGHT;
	}

	void Enemy::m_UpdatePosition()
	{
		switch (m_direction)
		{
		case LEFT:
			if (m_target.GetPhysicBodyRef()->GetPosition().x < m_physicBodyRef->GetPosition().x - 100)
				m_physicBodyRef->AddVelocity({ -m_speed, 0 }, m_clampVelocity);
			break;
		case RIGHT:
			if (m_target.GetPhysicBodyRef()->GetPosition().x > m_physicBodyRef->GetPosition().x + 100)
				m_physicBodyRef->AddVelocity({ m_speed, 0 }, m_clampVelocity);
			break;
		default:
			break;
		}
	}

	void Enemy::Draw()
	{
	}

	PhysicBodyRef Enemy::GetPhysicBodyRef()
	{
		return m_physicBodyRef;
	}


	//Update 


	void Enemy::InitLife() {
		
		//Varie celon le type d'Enemy 
		m_maxLifeEntity = 100;//default value
		m_lifeEntity = m_maxLifeEntity;

	}

	int Enemy::ReturnLife() {
		return m_lifeEntity;
	}

	void Enemy::UpdateLifeEntity(float lifeUpdate, bool typelifeUpdate) {

		if (typelifeUpdate == false) {

			m_lifeEntity -= lifeUpdate;

			if (m_lifeEntity <= 0 ) {
				m_lifeEntity = 0;
				//Destroy Enemy
			}

		}
		else {
			
			m_lifeEntity += lifeUpdate;

			if (m_lifeEntity > m_maxLifeEntity) {
				m_lifeEntity = 100;
			}
		}

	}


}