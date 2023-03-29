#include "stdafx.h"

namespace Snail
{
	MainState::MainState(GameDataRef data) : m_data(data), m_player(m_data), m_enemy(data, m_player)
	{
		m_physicBodyManager = PhysicBodyManager(data);
	}

	void MainState::Init()
	{
		m_InitBackground();
		m_InitView();

		Map map(m_data, "Resources/Data/Map/TestDebug.json");

		std::vector<PhysicBodyRef> refs = map.GetPhysicBodyRefs();

		for (int i = 0; i < refs.size(); i++)
		{
			m_physicBodyManager.AddPhysicBody(std::to_string(i), refs[i]);
		}

		m_timerBulletFire = 0;
		m_numberBullet = 0;

		m_player.Init(m_physicBodyManager);
		m_enemy.Init(m_physicBodyManager);

		/*m_physicBodyManager.AddPhysicBody("PLAYER", m_player.GetPhysicBodyRef());*/



		/**
		 * \brief Tests with dummy boxes.
		 * 
		 */
		//m_data->assetManager.LoadTexture("ENTITY_DUMMY", STATE_MAIN_DUMMY_ENTITY_TEST_FILEPATH);
		////ground
		//m_physicBodyManager.AddPhysicBody("GROUND", PhysicBodyRef(PhysicBody::CreateBoxBody(
		//	sf::Vector2f(1000.f, 100.f), sf::Vector2f(WINDOW_SCREEN_WIDTH / 2.f, 650.f), 1.f, true
		//)));
		//
		//// dummy box
		//m_physicBodyManager.AddPhysicBody("BOX", PhysicBodyRef(PhysicBody::CreateBoxBody(
		//	sf::Vector2f(16.f, 16.f), sf::Vector2f(WINDOW_SCREEN_WIDTH / 2.f, WINDOW_SCREEN_HEIGHT / 4.f), 0.5f, false,
		//	m_data->assetManager.GetTexture("ENTITY_DUMMY")
		//)));
		//
		//m_physicBodyManager.AddPhysicBody("BOX2", PhysicBodyRef(PhysicBody::CreateBoxBody(
		//	sf::Vector2f(16.f, 16.f), sf::Vector2f(WINDOW_SCREEN_WIDTH / 2.f, WINDOW_SCREEN_HEIGHT / 8.f), 0.5f, false,
		//	m_data->assetManager.GetTexture("ENTITY_DUMMY")
		//)));
		//
		//m_physicBodyManager.AddPhysicBody("BOX3", PhysicBodyRef(PhysicBody::CreateBoxBody(
		//	sf::Vector2f(16.f, 16.f), sf::Vector2f(WINDOW_SCREEN_WIDTH / 2.f, WINDOW_SCREEN_HEIGHT / 16.f), 0.5f, false,
		//	m_data->assetManager.GetTexture("ENTITY_DUMMY")
		//)));

		// ennemy
		/*m_physicBodyManager.AddPhysicBody("ENNEMY", m_enemy.GetPhysicBodyRef());*/
	}

	void MainState::m_InitBackground()
	{
		m_data->assetManager.LoadTexture("STATE_MAIN_BACKGROUND", STATE_MAIN_BACKGROUND_FILEPATH);
		m_background.setTexture(m_data->assetManager.GetTexture("STATE_MAIN_BACKGROUND"));
		m_background.scale(sf::Vector2f(0.25f, 0.25f));
	}

	void MainState::m_InitView()
	{
		m_view.setSize(sf::Vector2f(m_data->window.getSize().x, m_data->window.getSize().y));
		m_view.setCenter(sf::Vector2f(m_data->window.getSize().x / 2, m_data->window.getSize().y / 2));
		m_view.zoom(0.25f);
		//m_view.setRotation(45.f);
		m_data->window.setView(m_view);
	}

	void MainState::AddBullet()
	{
		sf::Vector2f mousePosition = (sf::Vector2f)sf::Mouse::getPosition(m_data->window);
		
		this->m_bullet = new BulletManager(m_data, m_player.GetPhysicBodyRef()->GetPosition(), (sf::Vector2f)m_data->window.mapPixelToCoords((sf::Vector2i)mousePosition));
		m_physicBodyManager.AddPhysicBody("Bullet" + m_numberBullet, m_bullet->m_physicBodyRef);
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
		m_UpdateView();
		
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
		m_enemy.Update(dt);
	}

	void MainState::m_UpdateView()
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			sf::Vector2f mousePosition = (sf::Vector2f)sf::Mouse::getPosition(m_data->window);
			mousePosition = Math::Clamp(mousePosition, sf::Vector2f(0.f, 0.f), (sf::Vector2f)m_data->window.getSize());
			m_background.setOrigin(mousePosition / /*value*/8.f); // Value = map size / background size
			m_view.setCenter(mousePosition);
		}
		else
		{
			m_background.setOrigin(m_player.GetPhysicBodyRef()->GetPosition() / /*value*/8.f); // Value = map size / background size
			m_view.setCenter(m_player.GetPhysicBodyRef()->GetPosition());
		}
		m_data->window.setView(m_view);
	}

	void MainState::Draw(float dt)
	{
		m_data->window.draw(m_background);
		if (!m_physicBodyManager.IsEmpty())
			m_physicBodyManager.Draw();
	}
}