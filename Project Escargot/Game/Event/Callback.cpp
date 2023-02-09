#include "stdafx.h"

namespace Snail
{
	void Callback(void (*ptr)())
	{
		(*ptr)();
	}

	void TestCallBack()
	{
		std::cout << "Shot fired !";
	}
}