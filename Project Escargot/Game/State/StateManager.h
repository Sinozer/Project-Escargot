#pragma once
#include "State.h"
namespace Snail
{
	typedef std::unique_ptr<State> StateRef;
	
	class StateManager
	{
	private:
		std::stack<StateRef> m_states;
		StateRef m_newState;

		bool m_isAdding;
		bool m_isRemoving;
	public:
		StateManager();

		void AddState(StateRef newState);
		void RemoveState();

		bool IsEmpty();

		void ProcessStateChanges();

		StateRef& GetActiveState();
	};
}