#include "stdafx.h"
#include "State.h"

namespace Snail
{
	unsigned int State::m_count = 0;
	
	void State::m_SetID()
	{
		ID = m_count;
		m_count++;
	}
}