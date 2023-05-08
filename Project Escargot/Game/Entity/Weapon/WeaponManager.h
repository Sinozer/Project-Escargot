#pragma once
#include "Game/Entity/EntityManager.h"
#include "Game/Entity/Weapon/Weapon.h"

namespace Snail
{
	class WeaponManager : public EntityManager
	{
	private :
		std::map <std::string, Weapon*> m_weapons;

		Weapon* m_activeWeapon = nullptr;

	public:
		~WeaponManager();

	public:
		void AddWeapon(std::string weaponName);

		Weapon* GetActive();
		void SetActive(std::string weaponName);
		
		void AddLoader(unsigned int amount = 1);

		float GetMunitions();
		float GetMaxMunitions();
		float GetLoaders();
		float GetDamages();
		
		void Use();

		void HandlerPos(sf::Vector2f handler);
		
		void Update();

		void Draw();
	};
}

