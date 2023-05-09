#include "stdafx.h"
#include "Weapon.h"

namespace Snail
{
	Weapon::Weapon()
	{
		m_previousWeaponState = WeaponState::IDLE;
		m_weaponState = WeaponState::IDLE;

		m_fireRate = .07f;
		m_fireRateDelta = 0.f;

		m_loaderAmount = 5.f;
		m_loaderAmountDelta = m_loaderAmount;

		m_loaderSize = 12.f;
		m_loaderSizeDelta = m_loaderSize;

		m_reloadTime = 1.6f;
		m_reloadTimeDelta = 0.f;
	}

	void Weapon::m_UpdateState()
	{
		switch (m_forceState)
		{
		case false:
			m_previousWeaponState = m_weaponState;

			if (m_loaderAmountDelta <= 0.f)
			{
				m_weaponState = Weapon::EMPTY;
				break;
			}
			else
				m_weaponState = Weapon::ATTACKING;

			if (m_loaderSizeDelta <= 0.f)
			{
				m_weaponState = Weapon::RELOADING;
				break;
			}
			else
				m_weaponState = Weapon::IDLE;

			if (m_reloadTimeDelta >= 0.01f)
			{
				m_weaponState = Weapon::RELOADING;
				break;
			}
			else
				m_weaponState = Weapon::IDLE;

			if (m_fireRateDelta >= 0.01f)
			{
				m_weaponState = Weapon::ATTACKING;
				break;
			}
			else
				m_weaponState = Weapon::IDLE;

			break;
		case true:
			break;
		}
		m_forceState = false;

		m_UpdateFromState();
	}

	bool Weapon::m_SetState(WeaponState state)
	{
		if (m_forceState) return false;

		m_forceState = true;
		m_previousWeaponState = m_weaponState;
		m_weaponState = state;

		return true;
	}

	void Weapon::m_UpdateFromState()
	{
		switch (m_weaponState)
		{
		case Weapon::IDLE:
			if (m_previousWeaponState != m_weaponState)

				switch (m_previousWeaponState)
				{
				case Snail::Weapon::ATTACKING:
					m_fireRateDelta = 0.f;
					break;
				case Snail::Weapon::RELOADING:
					m_reloadTimeDelta = 0.f;
					m_loaderSizeDelta = m_loaderSize;
					m_fireRateDelta = 0.f;
					break;
				}

			break;

		case Weapon::ATTACKING:
			if (m_previousWeaponState != m_weaponState)
			{
				m_loaderSizeDelta--;
				m_fireRateDelta = m_fireRate;
			}
			else
				m_fireRateDelta -= Game::m_data->deltaTime;
			break;

		case Weapon::RELOADING:
			if (m_previousWeaponState != m_weaponState)
			{
				m_reloadTimeDelta = m_reloadTime;
				m_loaderAmountDelta--;
			}
			else
				m_reloadTimeDelta = Math::Clamp(m_reloadTimeDelta - Game::m_data->deltaTime, 0.f, m_reloadTime);

			if (m_reloadTimeDelta <= 0.f)
				m_SetState(IDLE);

			break;

		case Weapon::EMPTY:
			break;
		}
	}
}