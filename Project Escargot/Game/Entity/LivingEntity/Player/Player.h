#pragma once
#include "Game/Entity/LivingEntity/LivingEntity.h"
#include "Game/Entity/Weapon/WeaponManager.h"
namespace Snail
{
	class Player : public LivingEntity
	{
	private:
		static Player* m_instance;

		/**
		 * \brief Constructor.
		 *
		 * \param data
		 */
		Player();

	public:
		static const bool IsInstance();
		static Player* GetInstance();
		static void DestroyInstance();
		
	private:
		WeaponManager m_weaponManager;
		
		void m_InitPhysicBody(sf::Vector2f position);
		void m_InitWeaponManager();
		void m_ChangeDirection(Direction direction = NONE);
		void m_UpdateWeaponManager();
		void m_DrawWeaponManager();

	public:
		~Player();
		
		void Init(sf::Vector2f position = sf::Vector2f(150, 150));

		void HandleInput();

		sf::Vector2f GetLocalPosition();
		
		void Update();

		void Draw();

		PhysicBodyRef GetPhysicBodyRef();

		void AddWeaponLoader(unsigned int amount = 1);

		float GetMunitions();
		std::string GetMunitionsString();
		float GetMaxMunitions();
		std::string GetMaxMunitionsString();
		float GetLoaders();
		std::string GetLoadersString();
		std::string GetAllMunitionsString();
		float GetDamages();
		std::string GetDamagesString();

	private:
		unsigned long int m_kills = 0;

		unsigned long int m_score = 0;

	public:
		unsigned long int GetKills();
		std::string GetKillsString();
		void AddKill();

		unsigned long int GetScore();
		std::string GetScoreString();
		void AddScore();
	};
}