#include "stdafx.h"
#include "Player.h"
namespace Snail
{
	Player* Player::m_instance = nullptr;

	Player* Player::GetInstance(GameDataRef data)
	{
		if (m_instance == nullptr)
			m_instance = new Player(data);

		return m_instance;
	}

	void Player::DestroyInstance()
	{
		delete m_instance;
		m_instance = nullptr;
	}
	
	Player::Player(GameDataRef data)
	{
		m_data = data;

		m_speed = 1.25f * PHYSIC_SCALE;
		m_jumpHeight = 2.f * PHYSIC_SCALE;
		m_clampVelocity = { m_speed, m_jumpHeight };
		bulletCount = 0;
	}

	Player::~Player()
	{
		if (m_weaponManager)
			delete(m_weaponManager);
	}

	void Player::Init(sf::Vector2f position)
	{
		m_InitPhysicBody(position);
		m_InitWeaponManager();
	}

	void Player::m_InitPhysicBody(sf::Vector2f position)
	{
		m_physicBodyRef = PhysicBodyRef(PhysicBody::CreateBoxBody(
			sf::Vector2f(16.f, 32.f), position, 0.f, false/*, AssetManager::GetInstance()->GetTexture("STATE_JOIN_BACKGROUND")*/
		));

		PhysicBodyManager::GetInstance()->AddPhysicBody("PLAYER", m_physicBodyRef);
	}

	void Player::m_InitWeaponManager()
	{
		m_weaponManager = new WeaponManager();
		m_weaponManager->AddWeapon("BOW");
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
			m_weaponManager->Use();
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
		m_weaponManager->Update(dt);
	}

	void Player::Draw()
	{
		m_DrawWeaponManager();
	}

	void Player::m_DrawWeaponManager()
	{
		m_weaponManager->Draw();
	}

	PhysicBodyRef Player::GetPhysicBodyRef()
	{
		return m_physicBodyRef;
	}
}
