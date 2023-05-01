#include "stdafx.h"
#include "StateManager.h"
#include "Game/Physic/PhysicBodyManager.h"

namespace Snail
{
	StateManager::StateManager()
	{
		m_isAdding = false;
		m_isRemoving = false;
	}

	void StateManager::AddState(StateRef newState)
	{
		m_isAdding = true;
		m_newState = move(newState);
	}

	void StateManager::RemoveState()
	{
		m_isRemoving = true;
	}

	bool StateManager::IsEmpty()
	{
		return m_states.empty();
	}

	void StateManager::ProcessStateChanges()
	{
		if (m_isRemoving && !m_states.empty())
		{
			PhysicBodyManager::DestroyInstance();
			m_states.top()->End();
			m_states.pop();
			m_isRemoving = false;
		}

		if (m_isAdding)
		{
			m_states.push(move(m_newState));
			m_states.top()->Init();
			m_isAdding = false;
		}
	}

	int StateManager::GetActiveStateID()
	{
		if (!m_states.empty())
			return m_states.top()->ID;
		return -1;
	}

	StateRef& StateManager::GetActiveState()
	{
		if (!m_states.empty())
			return m_states.top();
	}
}