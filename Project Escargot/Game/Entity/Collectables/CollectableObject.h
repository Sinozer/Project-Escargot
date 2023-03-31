#pragma once
#include "Game/Entity/Entity.h"
namespace Snail
{
	class CollectableObject : Entity
	{
	protected:

		PhysicBodyRef m_collectablePhysicBody;

		enum Type{
			Life = 0,
			Poison = 1,
		};
		Type m_type;
		float m_value;


	public:

		CollectableObject();
		~CollectableObject();
		void Init();
		void Update(float dt);
		void Draw();



		void m_InitPhysicBody();
		void m_CollectObject(Player livingEntity);
		void m_SetType(Type type);
		void m_SetValue(float value);
		PhysicBodyRef GetPhysicBodyRefCollectable();

	};
}
