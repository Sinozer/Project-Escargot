#include "stdafx.h"
#include "WeaponManager.h"
#include "Range/List/Bow/Bow.h"

namespace Snail
{
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
		m_activeWeapon->Init(sf::Vector2f(0,0));
    }

    float WeaponManager::GetMunitions()
    {
        return m_activeWeapon->GetMunitions();
    }

    float WeaponManager::GetMaxMunitions()
    {
		return m_activeWeapon->GetMaxMunitions();
    }

    float WeaponManager::GetLoaders()
    {
        return m_activeWeapon->GetLoaders();
    }

    float WeaponManager::GetDamages()
    {
        return m_activeWeapon->GetDamages();
    }

    void WeaponManager::Use()
    {
        if (!m_activeWeapon) return;
        m_activeWeapon->Use();
    }

    void WeaponManager::HandlerPos(sf::Vector2f handler)
    {
        m_activeWeapon->HandlerPos(handler);
    }
    
    void WeaponManager::Update()
    {
        m_activeWeapon->Update();
    }

    void WeaponManager::Draw()
    {
        m_activeWeapon->Draw();
    }
}
