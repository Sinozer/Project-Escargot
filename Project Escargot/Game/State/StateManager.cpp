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

	void StateManager::RemoveAllStates()
	{
		while (!m_states.empty())
			m_states.pop();
	}

	bool StateManager::IsEmpty()
	{
		return m_states.empty();
	}

	void StateManager::ProcessStateChanges()
	{
		if (m_isRemoving && !m_states.empty())
		{
			m_isRemoving = false;
			PhysicBodyManager::DestroyInstance();
			m_states.top()->End();
			m_states.pop();
		}

		if (m_isAdding)
		{
			m_isAdding = false;
			m_states.push(move(m_newState));
			m_states.top()->Init();
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

		throw std::exception("No active state");
	}

	StateRef& StateManager::GetPreviousState()
	{
		if (m_states.size() <= 1)
			throw std::exception("No previous state");

		StateRef temp = move(m_states.top());
		m_states.pop();

		StateRef& ret = m_states.top();
		m_states.push(move(temp));

		return ret;
	}
}