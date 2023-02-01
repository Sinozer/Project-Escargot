#include "stdafx.h"

namespace Snail
{
	ViewManager::ViewManager()
	{
		m_isAdding = false;
		m_isRemoving = false;
		m_isReplacing = false;
	}

	void ViewManager::AddView(StateRef newView, bool isReplacing)
	{
		m_isAdding = true;
		m_isReplacing = isReplacing;
		m_newView = move(newView);
	}

	void ViewManager::RemoveView()
	{
		m_isRemoving = true;
	}

	bool ViewManager::IsEmpty()
	{
		return m_states.empty();
	}

	void ViewManager::ProcessViewChanges()
	{
		if (m_isRemoving && !m_states.empty())
		{
			m_states.pop();

			m_isRemoving = false;
		}

		if (m_isAdding)
		{
			m_states.push(move(m_newView));
			m_states.top()->Init();
			m_isAdding = false;
		}
	}
}