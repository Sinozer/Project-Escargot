#pragma once
#include "Game/State/State.h"
namespace Snail
{
	/**
	 * \brief Template view class.
	 */
	class View : public State
	{
	private:
		bool m_isActive;
	public:
		bool IsActive() { return m_isActive; }
		void Activate() { m_isActive = true; }
		void Desactivate() { m_isActive = false; }
	};
}