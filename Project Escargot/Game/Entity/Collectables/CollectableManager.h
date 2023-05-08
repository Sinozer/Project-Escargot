#pragma once
#include "Game/Entity/Entity.h"
#include "Collectable.h"
namespace Snail
{
	class CollectableManager
	{
#pragma region Singleton
	private:
		static CollectableManager* m_instance;

		CollectableManager();

	public:
		static bool IsInstance();
		static CollectableManager* GetInstance();
		static void DestroyInstance();
#pragma endregion
		
#pragma region CollectableBehaviour
	private:
		std::vector<Collectable*> m_collectables;

	private:
		void m_UpdateCollectables();

	public:
		void AddCollectable(sf::Vector2f position);
		void AddCollectable(sf::Vector2f position, Collectable::Type type);
		void RemoveCollectable(int index);
		void RemoveFirstCollectable();
		void RemoveLastCollectable();
#pragma endregion

	public:
		~CollectableManager();

		void Update();
		void Draw();
	};
}
 