#include "stdafx.h"


namespace Snail
{
    void WeaponManager::AddWeapon(std::string weaponName)
    {
        m_weapons[weaponName] = new Bow(sf::Vector2f(0.f,0.f));
    }

    Weapon* WeaponManager::GetActive()
    {
        return m_activeWeapon;
    }

    void WeaponManager::SetActive(std::string weaponName)
    {
        if (!m_weapons.at(weaponName)) return;
        m_activeWeapon = m_weapons.at(weaponName);
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
