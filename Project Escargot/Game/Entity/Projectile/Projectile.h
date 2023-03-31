#pragma once
#include "../Entity.h"
namespace Snail
{
	/**
	 * \TODO Make it virtual
	 */
	class Projectile : public Entity
	{
	protected:
		unsigned int m_id;
	protected:
		GameDataRef m_data;
		PhysicBodyRef m_physicBodyRef;

		sf::Vector2f m_weaponPosition;
		sf::Vector2f m_targetPosition;


		float m_damage;
		float m_speed;
		float m_range;
	public:
		//virtual void AddBullet() = 0;
	};
}