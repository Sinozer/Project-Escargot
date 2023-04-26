#pragma once
namespace Snail
{
	class PhysicBody;
	typedef std::shared_ptr<PhysicBody> PhysicBodyRef;
	class PhysicBody
	{
	private:
		sf::RectangleShape m_body;

		bool m_canCollide;
		bool m_canGravitate;

		PhysicBody(sf::Vector2f position, float restitution,
			bool isStatic, bool canCollide, bool canGravitate, sf::Vector2f size);

		PhysicBody(sf::Vector2f position, float restitution,
			bool isStatic, sf::Vector2f size, sf::Texture& texture, bool canCollide, bool canGravitate);

		PhysicBody(sf::Vector2f position, float restitution,
			bool isStatic, sf::Vector2f size, sf::Texture& texture, sf::Vector2i texturePosition, bool canCollide, bool canGravitate);

		void m_Move(float dt);
	public:

		sf::Vector2f m_velocity;

		bool m_IsOnGround;
		
		float m_Restitution;
		
		bool m_IsStatic;

		static PhysicBody* CreateBoxBody(sf::Vector2f size, sf::Vector2f position, float restitution, bool isStatic, bool canCollide = true, bool canGravitate = true);

		static PhysicBody* CreateBoxBody(sf::Vector2f size, sf::Vector2f position, float restitution, bool isStatic, sf::Texture& texture, bool canCollide = true, bool canGravitate = true);
		
		static PhysicBody* CreateBoxBody(sf::Vector2f size, sf::Vector2f position, float restitution, bool isStatic, sf::Texture& texture, sf::Vector2i texturePosition, bool canCollide = true, bool canGravitate = true);
	
		void Rotate(float angle);

		sf::Vector2f GetScale();

		void Scale(sf::Vector2f scale);

		void SetPosition(sf::Vector2f position);

		sf::Vector2f GetPosition();

		void Move(sf::Vector2f step);

		void AddVelocity(sf::Vector2f step, sf::Vector2f clamp);

		sf::Vector2f GetHalfSize();

		bool CheckCollision(PhysicBodyRef other, sf::Vector2f& direction);

		void OnCollision(sf::Vector2f direction);

		void Update(float dt);

		void Draw(sf::RenderWindow& window);
	};
}