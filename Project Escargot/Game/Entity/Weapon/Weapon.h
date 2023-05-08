#pragma once
#include "../Entity.h"
#include "Game/Entity/Projectile/ProjectileManager.h"
namespace Snail
{
	/**
	 * \TODO Make it virtual
	 */
	class Weapon : public Entity
	{
#pragma region WeaponState
	public:
		enum WeaponState
		{
			IDLE,
			ATTACKING,
			RELOADING,
			EMPTY
		};
		
	protected:
		void m_UpdateState();
		bool m_SetState(WeaponState state);

	private:
		void m_UpdateFromState();

	protected:
		bool m_forceState;
		WeaponState m_previousWeaponState;
		WeaponState m_weaponState;
		
#pragma endregion

	protected:
		std::string m_name;

		sf::Vector2f m_wantedPosition;

		float m_offset;

	protected:
		/**
		 * \brief Amount of projectiles per seconds.
		 */
		float m_fireRate;
		float m_fireRateDelta;

		/**
		 * \brief Amount of loaders.
		 */
		float m_loaderAmount;
		float m_loaderAmountDelta;
		
		/**
		 * \brief Amount of projectiles per loader.
		 */
		float m_loaderSize;
		float m_loaderSizeDelta;

		/**
		 * \brief Amount of time to reload.
		 */
		float m_reloadTime;
		float m_reloadTimeDelta;

	protected:
		Weapon();

	public:

		inline void AddLoader(unsigned int amount = 1)
		{
			m_loaderAmountDelta += amount;
		}

		inline float GetMunitions()
		{
			return m_loaderSizeDelta;
		}
		inline float GetMaxMunitions()
		{
			return m_loaderSize;
		}
		inline float GetLoaders()
		{
			return m_loaderAmountDelta;
		}
		virtual float GetDamages() = 0;

		virtual void Use() = 0;

		virtual void Draw() = 0;

		virtual void Update() = 0;

		virtual void HandlerPos(sf::Vector2f handler) = 0;
	};
}

