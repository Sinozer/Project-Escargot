#pragma once
#include "Game/Entity/LivingEntity/LivingEntity.h"
#include "Game/Entity/Weapon/WeaponManager.h"


namespace Snail
{
	class Player : LivingEntity
	{
	private:
		GameDataRef m_data;
		WeaponManager m_weaponManager;

		
		void m_InitPhysicBody();
		void m_InitWeaponManager();
		void m_ChangeDirection(Direction direction = NONE);
		void m_UpdateWeaponManager(float dt);
		void m_DrawWeaponManager();
	public:
		int bulletCount;
		
		/**
		 * \brief Constructor.
		 * 
		 * \param data
		 */
		Player(GameDataRef data);
		
		void Init();

		void HandleInput();

		void Update(float dt);

		void Draw();

		PhysicBodyRef GetPhysicBodyRef();


		
		void InitLife();
		int ReturnLife() ;
		void UpdateLifeEntity(float lifeUpdate, bool typelifeUpdate);
		void ModifyMaxLifeEntity(float newMaxLife);
		


	};
}