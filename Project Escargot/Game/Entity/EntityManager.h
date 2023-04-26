#pragma once

namespace Snail
{
	class EntityManager
	{
	public:
		virtual void Update() = 0;
		virtual void Draw() = 0;
	};
}
