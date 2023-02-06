#include "stdafx.h"

namespace Snail
{
	PhysicBody::PhysicBody(sf::Vector2f position, float restitution,
		bool isStatic, sf::Vector2f size)
	{
		m_body.setPosition(position);
		m_body.setSize(size);
		m_body.setOrigin(size / 2.f);
		m_body.setFillColor(sf::Color::Transparent);
		m_velocity = sf::Vector2f(0, 0);
		m_IsOnGround = false;
		m_Restitution = restitution;
		m_IsStatic = isStatic;

		if (DEBUG)
		{
			m_body.setOutlineThickness(1.f);
			m_body.setOutlineColor(sf::Color::Green);
		}
	}

	PhysicBody::PhysicBody(sf::Vector2f position, float restitution,
		bool isStatic, sf::Vector2f size, sf::Texture texture)
	{
		m_body.setPosition(position);
		m_body.setTexture(&texture);
		m_body.setSize(size);
		m_body.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
		m_body.setOrigin(size / 2.f);
		m_body.setFillColor(sf::Color::Transparent);
		m_velocity = sf::Vector2f(0, 0);
		m_IsOnGround = false;
		m_Restitution = restitution;
		m_IsStatic = isStatic;

		if (DEBUG)
		{
			m_body.setOutlineThickness(1.f);
			m_body.setOutlineColor(sf::Color::Green);
		}
	}

	void PhysicBody::m_Move(float dt)
	{
		if (m_IsStatic) return;
		m_body.move(m_velocity * dt);

		m_velocity.y += (GAME_GRAVITY * dt);
	}

	PhysicBody* PhysicBody::CreateBoxBody(sf::Vector2f size, sf::Vector2f position, float restitution, bool isStatic)
	{
		restitution = Math::Clamp(restitution, 0.f, 1.f);

		return new PhysicBody(position, restitution, isStatic, size);
	}

	PhysicBody* PhysicBody::CreateBoxBody(sf::Vector2f size, sf::Vector2f position, float restitution, bool isStatic, sf::Texture texture)
	{
		restitution = Math::Clamp(restitution, 0.f, 1.f);

		return new PhysicBody(position, restitution, isStatic, size, texture);
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

	void PhysicBody::AddVelocity(sf::Vector2f step)
	{
		m_velocity += step; // Maybe clamp this step instead of make it = 0
	}

	sf::Vector2f PhysicBody::GetHalfSize()
	{
		return m_body.getSize() / 2.0f;
	}

	bool PhysicBody::CheckCollision(PhysicBodyRef other, sf::Vector2f& direction)
	{
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

	void PhysicBody::Update(float dt)
	{
		m_Move(dt);
	}

	void PhysicBody::Draw(sf::RenderWindow& window)
	{
		window.draw(m_body);
	}
}