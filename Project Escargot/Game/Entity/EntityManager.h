#pragma once

namespace Snail
{
	class EntityManager
	{
	public:
		virtual void Update(float dt) = 0;
		virtual void Draw() = 0;
	};
}
