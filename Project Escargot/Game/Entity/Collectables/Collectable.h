#pragma once
#include "Game/Entity/Entity.h"
namespace Snail
{
	class Collectable : public Entity
	{
	private:
		static unsigned int m_count;

	public:
		enum Type {
			LIFE,
			AMMO,

			null
		};

		struct LootType {
			Type type;
			float chance;
		};

	protected:
		std::vector<LootType> m_lootTable
		{
			{ LIFE, 0.5f },
			{ AMMO, 0.5f }
		};

		void m_RollLootTable();

		Type m_type = null;


	private:
		void m_InitPhysicBody(sf::Vector2f position);
		void m_Collect();

	public:
		Collectable();
		Collectable(Type type);
		~Collectable();
		void Init(sf::Vector2f position = sf::Vector2f(170, 170));
		void Update();
		void Draw();
	};
}
