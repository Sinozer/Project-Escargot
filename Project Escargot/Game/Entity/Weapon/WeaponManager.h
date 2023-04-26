#pragma once
#include "Game/Entity/EntityManager.h"
#include "Game/Entity/Weapon/Weapon.h"

namespace Snail
{
	class WeaponManager : public EntityManager
	{
	private :
		std::map <std::string, Weapon*> m_weapons;

		Weapon* m_activeWeapon;


	public:
		void AddWeapon(std::string weaponName);

		Weapon* GetActive();
		void SetActive(std::string weaponName);
		
		void Use();

		void Update();

		void Draw();
	};
}

