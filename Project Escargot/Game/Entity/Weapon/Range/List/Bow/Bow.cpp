#include "stdafx.h"
#include "Bow.h"


namespace Snail
{

	Bow::Bow(sf::Vector2f targetPosition)
	{
		m_projectileManager.SetProjectile(new Arrow());

		/*m_fireRate = .9f;
		m_fireRateDelta = 0.f;

		m_loaderAmount = 16.f;
		m_loaderAmountDelta = m_loaderAmount;

		m_loaderSize = 1.f;
		m_loaderSizeDelta = m_loaderSize;

		m_reloadTime = 1.f;
		m_reloadTimeDelta = 0.f;*/

		m_fireRate = .2f;
		m_fireRateDelta = 0.f;

		m_loaderAmount = 16.f;
		m_loaderAmountDelta = m_loaderAmount;

		m_loaderSize = 100.f;
		m_loaderSizeDelta = m_loaderSize;

		m_reloadTime = 1.f;
		m_reloadTimeDelta = 0.f;
	}

	Bow::~Bow()
	{
	}

	float Bow::GetDamages()
	{
		return m_damageMultiplier * m_projectileManager.GetDamages();
	}


	void Bow::Init(sf::Vector2f position = sf::Vector2f(150, 150))
	{
		m_InitPhysicBody(position);
	}

	void Bow::m_InitPhysicBody(sf::Vector2f position)
	{
		sf::Texture& texture = AssetManager::GetInstance()->LoadTexture("CROSSHAIR", STATE_GAME_WEAPON_CROSSHAIR_FILEPATH);
		texture.setSmooth(true);

		m_physicBodyRef = PhysicBodyRef(PhysicBody::CreateBoxBody(
			position, 0.f, true, texture, false, false
		));

		m_physicBodyRef->Scale(sf::Vector2f(0.14f, 0.14f));

		PhysicBodyManager::GetInstance()->AddPhysicBody("BOW", m_physicBodyRef);
	}

	void Bow::Use()
	{
		if (m_weaponState != WeaponState::IDLE) return;

		if (!m_SetState(WeaponState::ATTACKING)) return;
		
		AssetManager::GetInstance()->LoadSoundBuffer("SFX_BOW_SHOOT", AUDIO_SFX_BOW_SHOOT_FILEPATH);
		AssetManager::GetInstance()->PlaySound("SFX_BOW_SHOOT");

		m_projectileManager.Shoot(calc);
	}

	void Bow::HandlerPos(sf::Vector2f handler)
	{ 
		float angle = std::atan2f(InputManager::GetInstance()->GetMousePosition().y - handler.y, InputManager::GetInstance()->GetMousePosition().x - handler.x);
		sf::Vector2f out = sf::Vector2f(std::cos(angle), std::sin(angle));
		
		double normX = handler.x/std::sqrt(std::pow(InputManager::GetInstance()->GetMousePosition().x, 2) - std::pow(handler.x, 2));
		double normY = handler.y/std::sqrt(std::pow(InputManager::GetInstance()->GetMousePosition().y, 2) - std::pow(handler.y, 2));
		calc = handler + out * 50.f;
	}
	
	void Bow::Update()
	{
		m_UpdateState();

		m_physicBodyRef->SetPosition(calc);
		m_projectileManager.Update();
	}

	void Bow::Draw()
	{
		m_projectileManager.Draw();
	}
}
