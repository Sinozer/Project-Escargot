#include "stdafx.h"

namespace Snail
{
	Player::Player(GameDataRef data)
	{
		m_data = data;

		m_speed = 1.25f * PHYSIC_SCALE;
		m_jumpHeight = 1.f * PHYSIC_SCALE;
		m_clampVelocity = { m_speed, m_jumpHeight };
		bulletCount = 0;
	}

	void Player::Init()
	{

		m_InitPhysicBody();
		m_InitWeaponManager();
		m_InitLife();
		/*
		UpdateLifeEntity(15, false);
		UpdateLifeEntity(30 , true);
		*/
	}

	void Player::m_InitPhysicBody()
	{
		m_physicBodyRef = PhysicBodyRef(PhysicBody::CreateBoxBody(
			sf::Vector2f(16.f, 32.f), sf::Vector2f(150, 150), 0.f, false/*, m_data->assetManager.GetTexture("STATE_JOIN_BACKGROUND")*/
		));
	}

	void Player::m_InitWeaponManager()
	{
		m_weaponManager.AddWeapon("BOW");
	}


	void Player::HandleInput()
	{
		m_physicBodyRef->m_velocity.x = 0.f;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			m_physicBodyRef->AddVelocity({ -m_speed, 0 }, m_clampVelocity);
			m_ChangeDirection(LEFT);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			m_physicBodyRef->AddVelocity({ m_speed, 0 }, m_clampVelocity);
			m_ChangeDirection(RIGHT);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_physicBodyRef->m_IsOnGround)
		{
			m_physicBodyRef->m_IsOnGround = false;
			m_physicBodyRef->m_velocity.y = -sqrtf(2.0f * GAME_GRAVITY * m_jumpHeight);
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			//bulletCount++;
			m_weaponManager.Use();
		}

		//if (DEBUG)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			m_physicBodyRef->SetPosition({ 150, 150 });
		}

	}

	void Player::m_ChangeDirection(Direction direction)
	{
		m_direction = direction;
	}

	void Player::Update(float dt)
	{
		m_UpdateWeaponManager(dt);
	}

	void Player::m_UpdateWeaponManager(float dt)
	{
		m_weaponManager.Update(dt);
	}

	void Player::Draw()
	{
		m_DrawWeaponManager();
	}

	void Player::m_DrawWeaponManager()
	{
		m_weaponManager.Draw();
	}

	PhysicBodyRef Player::GetPhysicBodyRef()
	{
		return m_physicBodyRef;
	}

	
	// Update possible 

	void Player::m_InitLife(){

		m_maxLifeEntity = 100; // faire varier celon certaines conditions ou autre 
		m_lifeEntity = m_maxLifeEntity;
		std::cout << "Max Begin :" << m_maxLifeEntity << std::endl;
		std::cout << "Life Begin :" << m_lifeEntity << std::endl;
	}

	int Player::ReturnLife() {
		return m_lifeEntity;
	}

	void Player::UpdateLifeEntity(float lifeUpdate, bool typelifeUpdate) {

		if (typelifeUpdate == false) {

			m_lifeEntity -= lifeUpdate;

			if (m_lifeEntity < 0) {
				m_lifeEntity = 0;

				// Game Over
				//Destroy the Player

			}
			/*
			std::cout << "Life Down:" << lifeUpdate << std::endl;
			*/
		}
		else {
			
			m_lifeEntity += lifeUpdate;

			if (m_lifeEntity > m_maxLifeEntity) {
				m_lifeEntity = 100;
			}
			/*
			std::cout << "Life Up:" << lifeUpdate;
			*/
		}
		/*
		std::cout << "Actual life :" << m_lifeEntity << std::endl;
		*/
	}

	void Player::ModifyMaxLifeEntity(float newMaxLife) {
		m_maxLifeEntity = newMaxLife;
	}

}
