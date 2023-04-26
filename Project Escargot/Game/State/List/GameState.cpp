#include "stdafx.h"
#include "GameState.h"
#include "Game/Map/Map.h"
namespace Snail
{
	GameState::GameState(GameDataRef data) : m_data(data), m_spawner(m_data)
	{
		// = PhysicBodyManager(data);

		m_player = Player::GetInstance(data);
	}

	void GameState::Init()
	{
		m_InitBackground();
		m_InitView();

		Map map(m_data, "Resources/Data/Map/TestDebug.json");

		std::vector<PhysicBodyRef> refs = map.GetPhysicBodyRefs();

		for (int i = 0; i < refs.size(); i++)
		{
			PhysicBodyManager::GetInstance()->AddPhysicBody(std::to_string(i), refs[i]);
		}

		m_timerBulletFire = 0;
		m_numberBullet = 0;

		m_player->Init();
		m_spawner.Init();
		m_collectable.Init();

		Enemy test(GameDataRef data);


		PhysicBodyManager::GetInstance()->AddPhysicBody("PLAYER", m_player->GetPhysicBodyRef());
	}

	void GameState::m_InitBackground()
	{
		AssetManager::GetInstance()->LoadTexture("STATE_MAIN_BACKGROUND", STATE_MAIN_BACKGROUND_FILEPATH);
		m_background.setTexture(AssetManager::GetInstance()->GetTexture("STATE_MAIN_BACKGROUND"));
		m_background.scale(sf::Vector2f(0.25f, 0.25f));
	}

	void GameState::m_InitView()
	{
		m_view.setSize(sf::Vector2f(m_data->window.getSize().x, m_data->window.getSize().y));
		m_view.setCenter(sf::Vector2f(m_data->window.getSize().x / 2, m_data->window.getSize().y / 2));
		m_view.zoom(0.25f);
		//m_view.setRotation(45.f);
		m_data->window.setView(m_view);
	}

	void GameState::m_InitUIManager()
	{
	}

	void GameState::AddBullet()
	{
		sf::Vector2f mousePosition = (sf::Vector2f)sf::Mouse::getPosition(m_data->window);
		
		this->m_bullet = new ProjectileManager(m_data, m_player->GetPhysicBodyRef()->GetPosition(), (sf::Vector2f)m_data->window.mapPixelToCoords((sf::Vector2i)mousePosition));
		PhysicBodyManager::GetInstance()->AddPhysicBody("Bullet" + m_numberBullet, m_bullet->m_physicBodyRef);
		m_timerBulletFire = 0;
		m_numberBullet++;
	}

	void GameState::HandleInput()
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

		m_tempBulletCount = m_player->bulletCount;
		m_player->HandleInput();
	}

	void GameState::Update(float dt)
	{
		m_UpdateView();
		
		PhysicBodyManager::GetInstance()->Update(dt);
		m_player->Update(dt);
		m_timerBulletFire++;
		if (m_player->bulletCount > this->m_tempBulletCount && m_timerBulletFire > 10)
		{

			if (m_numberBullet > 5)
			{
				for (int i = 0; i < m_numberBullet; i++)
					PhysicBodyManager::GetInstance()->RemovePhysicBody("Bullet" + i);
				m_numberBullet = 0;
			}
			AddBullet();
		}
		m_spawner.Update(dt);

		m_UpdateUIManager(dt);
	}

	void GameState::m_UpdateView()
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			sf::Vector2f mousePosition = (sf::Vector2f)sf::Mouse::getPosition(m_data->window);
			mousePosition = Math::Clamp(mousePosition, sf::Vector2f(0.f, 0.f), (sf::Vector2f)m_data->window.getSize());
			m_background.setOrigin(mousePosition / /*value*/8.f); // Value = map size / background size
			m_view.setCenter(mousePosition);
			m_spawner.Spawn();
		}
		else
		{
			m_background.setOrigin(m_player->GetPhysicBodyRef()->GetPosition() / /*value*/8.f); // Value = map size / background size
			m_view.setCenter(m_player->GetPhysicBodyRef()->GetPosition());
		}
		m_data->window.setView(m_view);
	}

	void GameState::m_UpdateUIManager(float dt)
	{
		m_uiManager.Update((sf::Vector2i)InputManager::GetInstance(m_data->window)->GetMousePosition(), dt);
	}

	void GameState::Draw(float dt)
	{
		m_data->window.draw(m_background);
		if (!PhysicBodyManager::GetInstance()->IsEmpty())
			PhysicBodyManager::GetInstance()->Draw();

		m_DrawUIManager();
	}

	void GameState::m_DrawUIManager()
	{
		m_uiManager.Draw(m_data->window);
	}
}