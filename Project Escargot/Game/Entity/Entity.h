#pragma once
#include "../Physic/PhysicBody.h"
namespace Snail
{
	/**
	 * \TODO Make it virtual
	 */
	class Entity : public PhysicBodyRef
	{
	protected:
		std::string m_name;
		
		float m_jumpHeight;

	public:
		virtual void Init() = 0;

		virtual void Update(float dt) = 0;

		virtual void Draw() = 0;
	};
}