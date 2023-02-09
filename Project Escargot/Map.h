#pragma once
namespace Snail
{
	class Map
	{
	private:
		std::vector<std::vector<int>> m_map;

	public:
		Map();
		~Map();

		void Init();

		void Update();
		void Draw();
	};
}