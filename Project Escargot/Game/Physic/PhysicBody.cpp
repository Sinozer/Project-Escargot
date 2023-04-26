#include "stdafx.h"
#include "PhysicBody.h"
namespace Snail
{
	PhysicBody::PhysicBody(sf::Vector2f position, float restitution,
		bool isStatic, bool canCollide, bool canGravitate, sf::Vector2f size)
	{
		m_body.setPosition(position);
		m_body.setSize(size);
		m_body.setOrigin(size / 2.f);
		m_body.setFillColor(sf::Color::Green);
		m_velocity = sf::Vector2f(0, 0);
		m_IsOnGround = false;
		m_Restitution = restitution;
		m_IsStatic = isStatic;

		m_canCollide = canCollide;
		m_canGravitate = canGravitate;

		if (DEBUG)
		{
			m_body.setOutlineThickness(1.f);
			m_body.setOutlineColor(sf::Color::Black);
		}
	}

	PhysicBody::PhysicBody(sf::Vector2f position, float restitution,
		bool isStatic, sf::Vector2f size, sf::Texture& texture, bool canCollide, bool canGravitate)
	{
		m_body.setPosition(position);
		m_body.setTexture(&texture);
		m_body.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
		m_body.setSize(size);
		m_body.setOrigin(size / 2.f);
		m_velocity = sf::Vector2f(0, 0);
		m_IsOnGround = false;
		m_Restitution = restitution;
		m_IsStatic = isStatic;

		m_canCollide = canCollide;
		m_canGravitate = canGravitate;

		if (DEBUG)
		{
			m_body.setOutlineThickness(1.f);
			m_body.setOutlineColor(sf::Color::Black);
		}
	}

	PhysicBody::PhysicBody(sf::Vector2f position, float restitution,
		bool isStatic, sf::Vector2f size, sf::Texture& texture, sf::Vector2i texturePosition, bool canCollide, bool canGravitate)
	{
		m_body.setPosition(position);
		m_body.setTexture(&texture);
		m_body.setTextureRect(sf::IntRect(texturePosition.x, texturePosition.y, size.x, size.y));
		m_body.setSize(size);
		m_body.setOrigin(size / 2.f);
		m_velocity = sf::Vector2f(0, 0);
		m_IsOnGround = false;
		m_Restitution = restitution;
		m_IsStatic = isStatic;

		m_canCollide = canCollide;
		m_canGravitate = canGravitate;

		if (DEBUG)
		{
			m_body.setOutlineThickness(1.f);
			m_body.setOutlineColor(sf::Color::Black);
		}
	}

	void PhysicBody::m_Move()
	{
		if (m_IsStatic) return;
		m_body.move(m_velocity * Game::m_data->deltaTime);

		if (m_canGravitate)
			m_velocity.y += (GAME_GRAVITY * Game::m_data->deltaTime * 1.5f);
	}

	PhysicBody* PhysicBody::CreateBoxBody(sf::Vector2f size, sf::Vector2f position, float restitution, bool isStatic, bool canCollide, bool canGravitate)
	{
		restitution = Math::Clamp(restitution, 0.f, 1.f);

		return new PhysicBody(position, restitution, isStatic, canCollide, canGravitate, size);
	}

	PhysicBody* PhysicBody::CreateBoxBody(sf::Vector2f size, sf::Vector2f position, float restitution, bool isStatic, sf::Texture& texture, bool canCollide, bool canGravitate)
	{
		restitution = Math::Clamp(restitution, 0.f, 1.f);

		return new PhysicBody(position, restitution, isStatic, size, texture, canCollide, canGravitate);
	}

	PhysicBody* PhysicBody::CreateBoxBody(sf::Vector2f size, sf::Vector2f position, float restitution, bool isStatic, sf::Texture& texture, sf::Vector2i texturePosition, bool canCollide, bool canGravitate)
	{
		restitution = Math::Clamp(restitution, 0.f, 1.f);

		return new PhysicBody(position, restitution, isStatic, size, texture, texturePosition, canCollide, canGravitate);
	}

	void PhysicBody::Rotate(float angle)
	{
		m_body.rotate(angle);
	}

	sf::Vector2f PhysicBody::GetScale()
	{
		return m_body.getScale();
	}

	void PhysicBody::Scale(sf::Vector2f scale)
	{
		m_body.scale(scale);
	}

	void PhysicBody::SetPosition(sf::Vector2f position)
	{
		m_body.setPosition(position);
	}

	sf::Vector2f PhysicBody::GetPosition()
	{
		return m_body.getPosition();
	}

	void PhysicBody::Move(sf::Vector2f step)
	{
		if (m_IsStatic) return;
		m_body.move(step);
	}

	void PhysicBody::AddVelocity(sf::Vector2f step, sf::Vector2f clamp)
	{
		if (m_IsStatic) return;
		m_velocity += step;
		m_velocity.x = Math::Clamp(m_velocity.x, -clamp.x, clamp.x);
	}

	sf::Vector2f PhysicBody::GetHalfSize()
	{
		return sf::Vector2f(m_body.getGlobalBounds().width, m_body.getGlobalBounds().height) / 2.0f;
	}

	bool PhysicBody::CheckCollision(PhysicBodyRef other, sf::Vector2f& direction)
	{
		if (!m_canCollide || !other->m_canCollide) return false;

		sf::Vector2f otherPosition = other->GetPosition();
		sf::Vector2f otherHalfSize = other->GetHalfSize();

		float dX = otherPosition.x - m_body.getPosition().x;
		float dY = otherPosition.y - m_body.getPosition().y;

		float intersectX = std::abs(dX) - (otherHalfSize.x + GetHalfSize().x);
		float intersectY = std::abs(dY) - (otherHalfSize.y + GetHalfSize().y);

		if (intersectX >= 0.0f || intersectY >= 0.0f) return false;

		if (intersectX > intersectY)
		{
			if (dX > 0.0f)
			{
				Move({ intersectX * (1.10f - m_Restitution), 0.0f });
				other->Move({ -intersectX * other->m_Restitution, 0.0f });

				direction = { 1.0f, 0.0f };
			}
			else
			{
				Move({ -intersectX * (1.10f - m_Restitution), 0.0f });
				other->Move({ intersectX * other->m_Restitution, 0.0f });

				direction = { -1.0f, 0.0f };
			}
		}
		else
		{
			if (dY > 0.0f)
			{
				Move({ 0.0f, intersectY * (1.10f - m_Restitution) });
				other->Move({ 0.0f, -intersectY * other->m_Restitution });

				direction = { 0.0f, 1.0f };
			}
			else
			{
				Move({ 0.0f, -intersectY * (1.10f - m_Restitution) });
				other->Move({ 0.0f, intersectY * other->m_Restitution });

				direction = { 0.0f, -1.0f };
			}
		}
		return true;
	}

	void PhysicBody::OnCollision(sf::Vector2f direction)
	{
		if (direction.x < 0.0f)
		{
			m_velocity.x = 0.0f;
		}
		else if (direction.x > 0.0f)
		{
			m_velocity.x = 0.0f;
		}
		if (direction.y < 0.0f)
		{
			m_velocity.y = 0.0f;
		}
		else if (direction.y > 0.0f)
		{
			m_IsOnGround = true;
			m_velocity.y = 0.0f;
		}
	}

	void PhysicBody::Update()
	{
		m_Move();
	}

	void PhysicBody::Draw(sf::RenderWindow& window)
	{
		window.draw(m_body);
	}
}