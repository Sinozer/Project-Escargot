#pragma once
#include "View.h"
/**
 * TODO
 */
namespace Snail
{
	typedef std::unique_ptr<State> ViewRef;

	class ViewManager
	{
	private:
		std::stack<StateRef> m_states;
		ViewRef m_newView;

		bool m_isAdding;
		bool m_isRemoving;
		bool m_isReplacing;
	public:
		ViewManager();

		void AddView(ViewRef newView, bool isReplacing = true);
		void RemoveView();

		bool IsEmpty();

		void ProcessViewChanges();
	};
}