#include "stdafx.h"
#include "Collectable.h"
#include "Game/Entity/LivingEntity/Player/Player.h"
namespace Snail
{
	unsigned int Collectable::m_count = 0;

	Collectable::Collectable()
	{
		m_RollLootTable();
	}

	Collectable::Collectable(Type type)
	{
		m_type = type;
	}

	Collectable::~Collectable()
	{
	}

	void Collectable::m_RollLootTable()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> dis(0.0f, 1.0f);

		float roll = dis(gen);

		float cumulativeChance = 0.f;
		for (auto& loot : m_lootTable) {
			cumulativeChance += loot.chance;
			if (roll <= cumulativeChance) {
				m_type = loot.type;
				break;
			}
		}

		if (m_type == null)
			m_type = m_lootTable.back().type;
	}

	void Collectable::Init(sf::Vector2f position)
	{
		m_InitPhysicBody(position);
	}

	void Collectable::m_InitPhysicBody(sf::Vector2f position)
	{
		m_physicBodyRef = PhysicBodyRef(PhysicBody::CreateBoxBody(
			position, 0.f, false, AssetManager::GetInstance()->GetTexture("Collectable_" + std::to_string(m_type))
		));

		m_physicBodyRef->Masks = MASK_COLLECTABLE;
		m_physicBodyRef->CollideMasks = MASK_MAP;
		m_physicBodyRef->TriggerMasks = MASK_PLAYER;

		m_physicBodyRef->Velocity = sf::Vector2f((rand() % 100 - 50.f), -60.f);

		Name = "Collectable" + std::to_string(m_count++);

		PhysicBodyManager::GetInstance()->AddPhysicBody(Name, m_physicBodyRef);
	}

	void Collectable::Update()
	{
		if (!m_physicBodyRef->IsTriggered) return;

		if ((m_physicBodyRef->TriggeredMasks & MASK_PLAYER) == MASK_PLAYER)
		{
			m_Collect();
			IsDeleted = true;
			PhysicBodyManager::GetInstance()->RemovePhysicBody(Name);
		}

		m_physicBodyRef->IsTriggered = false;
		m_physicBodyRef->TriggeredMasks = MASK_EMPTY;
	}

	void Collectable::Draw()
	{
	}

	void Collectable::m_Collect()
	{
		switch (m_type)
		{
		case LIFE:
			Player::GetInstance()->RestoreLife();
			std::cout << "LIFE" << std::endl;
			break;
		case AMMO:
			Player::GetInstance()->AddWeaponLoader(2);
			std::cout << "AMMO" << std::endl;
			break;
		}
	}
}