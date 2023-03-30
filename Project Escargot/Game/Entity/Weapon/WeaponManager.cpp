#include "stdafx.h"


namespace Snail
{
	WeaponManager::WeaponManager(PhysicBodyManager& physicBodyManager) : m_physicBodyManager(physicBodyManager)
    {

    }

    void WeaponManager::AddWeapon(std::string weaponName)
    {
        m_weapons[weaponName] = new Bow(sf::Vector2f(0.f,0.f));
        SetActive(weaponName);
    }

    Weapon* WeaponManager::GetActive()
    {
        return m_activeWeapon;
    }

    void WeaponManager::SetActive(std::string weaponName)
    {
        if (!m_weapons.at(weaponName)) return;
		// Remove precedent weapon from physicBodyManager
        
        
        m_activeWeapon = m_weapons.at(weaponName);
		m_activeWeapon->Init(m_physicBodyManager);
    }

    void WeaponManager::Use()
    {
        if (!m_activeWeapon) return;
        m_activeWeapon->Use();
    }

    void WeaponManager::Update(float dt)
    {
        m_activeWeapon->Update(dt);
    }

    void WeaponManager::Draw()
    {
        m_activeWeapon->Draw();
    }
}
