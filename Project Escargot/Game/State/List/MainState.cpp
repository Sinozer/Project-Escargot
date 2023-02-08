#include "stdafx.h"

namespace Snail
{
	MainState::MainState(GameDataRef data) : m_data(data), m_player(m_data), m_ennemy(data, m_player)
	{
		m_physicBodyManager = PhysicBodyManager(data);
	}

	void MainState::Init()
	{
		m_timerBulletFire = 0;
		m_numberBullet = 0;
		m_data->assetManager.LoadTexture("STATE_JOIN_BACKGROUND", STATE_JOIN_BACKGROUND_FILEPATH);
		m_background.setTexture(m_data->assetManager.GetTexture("STATE_JOIN_BACKGROUND"));

		m_player.Init();
		m_ennemy.Init();

		m_physicBodyManager.AddPhysicBody("PLAYER", m_player.m_physicBodyRef);

		// ground
		m_physicBodyManager.AddPhysicBody("GROUND", PhysicBodyRef(PhysicBody::CreateBoxBody(
			sf::Vector2f(1000.f, 100.f), sf::Vector2f(WINDOW_SCREEN_WIDTH / 2.f, 650.f), 1.f, true
		)));

		// dummy box
		m_physicBodyManager.AddPhysicBody("BOX", PhysicBodyRef(PhysicBody::CreateBoxBody(
			sf::Vector2f(100.f, 100.f), sf::Vector2f(WINDOW_SCREEN_WIDTH / 2.f, WINDOW_SCREEN_HEIGHT / 4.f), 0.5f, false
		)));

		m_physicBodyManager.AddPhysicBody("BOX2", PhysicBodyRef(PhysicBody::CreateBoxBody(
			sf::Vector2f(100.f, 100.f), sf::Vector2f(WINDOW_SCREEN_WIDTH / 2.f, WINDOW_SCREEN_HEIGHT / 8.f), 0.5f, false
		)));

		m_physicBodyManager.AddPhysicBody("BOX3", PhysicBodyRef(PhysicBody::CreateBoxBody(
			sf::Vector2f(100.f, 100.f), sf::Vector2f(WINDOW_SCREEN_WIDTH / 2.f, WINDOW_SCREEN_HEIGHT / 16.f), 0.5f, false
		)));

		// ennemy
		m_physicBodyManager.AddPhysicBody("ENNEMY", m_ennemy.m_physicBodyRef);
	}

	void MainState::AddBullet()
	{
		sf::Vector2f mousePosition = (sf::Vector2f)sf::Mouse::getPosition(m_data->window);
		
		this->m_bullet = new BulletManager(m_data, m_player.m_physicBodyRef->GetPosition(), m_player.m_playerDir, mousePosition);
		m_physicBodyManager.AddPhysicBody("Bullet"+ m_numberBullet, m_bullet->m_physicBodyRef);
		m_timerBulletFire = 0;
		m_numberBullet++;
	}

	void MainState::HandleInput()
	{
		sf::Event event;

		while (m_data->window.pollEvent(event))
			switch (event.type)
			{
			case sf::Event::Closed:
				m_data->window.close();
				break;
			}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			m_data->stateManager.RemoveState();

		m_tempBulletCount = m_player.bulletCount;
		m_player.HandleInput();
	}

	void MainState::Update(float dt)
	{
		m_physicBodyManager.Update(dt);
		m_player.Update(dt);
		m_timerBulletFire++;
		if (m_player.bulletCount > this->m_tempBulletCount && m_timerBulletFire > 10) 
		{

			if (m_numberBullet > 5)
			{
				for (int i = 0; i < m_numberBullet; i++)
					m_physicBodyManager.RemovePhysicBody("Bullet" + i);
				m_numberBullet = 0;
			}
			AddBullet();
		}
		
		m_ennemy.Update(dt);
	}

	void MainState::Draw(float dt)
	{
		m_data->window.draw(m_background);
		if (!m_physicBodyManager.IsEmpty())
			m_physicBodyManager.Draw();
	}
}