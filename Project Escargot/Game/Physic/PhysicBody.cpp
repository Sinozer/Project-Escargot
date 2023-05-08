#include "stdafx.h"
#include "PhysicBody.h"
namespace Snail
{
#pragma region Constructors
	PhysicBody::PhysicBody(sf::Vector2f position, float restitution,
		bool isStatic, bool canCollide, bool canGravitate, sf::Vector2f size)
	{
		m_body.setPosition(position);
		m_body.setSize(size);
		m_body.setOrigin(size / 2.f);
		m_body.setFillColor(sf::Color::Green);
		Velocity = sf::Vector2f(0, 0);
		IsOnGround = false;
		Restitution = restitution;
		IsStatic = isStatic;

		m_canCollide = canCollide;
		m_canGravitate = canGravitate;

		Masks = MASK_EMPTY;
		CollideMasks = MASK_EMPTY;
		TriggerMasks = MASK_EMPTY;
		TriggeredMasks = MASK_EMPTY;
		IsTriggered = false;

		if (DEBUG)
		{
			m_body.setOutlineThickness(1.f);
			m_body.setOutlineColor(sf::Color::Black);
		}
	}

	PhysicBody::PhysicBody(sf::Vector2f position, float restitution,
		bool isStatic, sf::Texture& texture, bool canCollide, bool canGravitate)
	{
		m_body.setPosition(position);
		m_body.setTexture(&texture);
		m_body.setSize((sf::Vector2f)texture.getSize());
		m_body.setOrigin(m_body.getSize() / 2.f);
		Velocity = sf::Vector2f(0, 0);
		IsOnGround = false;
		Restitution = restitution;
		IsStatic = isStatic;

		m_canCollide = canCollide;
		m_canGravitate = canGravitate;

		Masks = MASK_EMPTY;
		CollideMasks = MASK_EMPTY;
		TriggerMasks = MASK_EMPTY;
		TriggeredMasks = MASK_EMPTY;
		IsTriggered = false;

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
		m_body.setTextureRect(sf::IntRect(texturePosition.x, texturePosition.y, (int)size.x, (int)size.y));
		m_body.setSize(size);
		m_body.setOrigin(size / 2.f);
		Velocity = sf::Vector2f(0, 0);
		IsOnGround = false;
		Restitution = restitution;
		IsStatic = isStatic;

		m_canCollide = canCollide;
		m_canGravitate = canGravitate;

		Masks = MASK_EMPTY;
		CollideMasks = MASK_EMPTY;
		TriggerMasks = MASK_EMPTY;
		TriggeredMasks = MASK_EMPTY;
		IsTriggered = false;

		if (DEBUG)
		{
			m_body.setOutlineThickness(1.f);
			m_body.setOutlineColor(sf::Color::Black);
		}
	}
#pragma endregion

	void PhysicBody::m_Move()
	{
		if (IsStatic) return;
		m_body.move(Velocity * Game::m_data->deltaTime);

		if (m_canGravitate)
			Velocity.y += Math::Clamp((GAME_GRAVITY * Game::m_data->deltaTime * 1.5f), -GAME_GRAVITY / 10.f, GAME_GRAVITY / 10.f);
	}

#pragma region Constructors
	PhysicBody* PhysicBody::CreateBoxBody(sf::Vector2f size, sf::Vector2f position, float restitution, bool isStatic, bool canCollide, bool canGravitate)
	{
		restitution = Math::Clamp(restitution, 0.f, 1.f);

		return new PhysicBody(position, restitution, isStatic, canCollide, canGravitate, size);
	}

	PhysicBody* PhysicBody::CreateBoxBody(sf::Vector2f position, float restitution, bool isStatic, sf::Texture& texture, bool canCollide, bool canGravitate)
	{
		restitution = Math::Clamp(restitution, 0.f, 1.f);

		return new PhysicBody(position, restitution, isStatic, texture, canCollide, canGravitate);
	}

	PhysicBody* PhysicBody::CreateBoxBody(sf::Vector2f size, sf::Vector2f position, float restitution, bool isStatic, sf::Texture& texture, sf::Vector2i texturePosition, bool canCollide, bool canGravitate)
	{
		restitution = Math::Clamp(restitution, 0.f, 1.f);

		return new PhysicBody(position, restitution, isStatic, size, texture, texturePosition, canCollide, canGravitate);
	}
#pragma endregion

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
		if (IsStatic) return;
		m_body.move(step);
	}

	void PhysicBody::AddVelocity(sf::Vector2f step, sf::Vector2f clamp)
	{
		if (IsStatic) return;
		Velocity += step;
		Velocity.x = Math::Clamp(Velocity.x, -clamp.x, clamp.x);
	}

	sf::Vector2f PhysicBody::GetHalfSize()
	{
		return sf::Vector2f(m_body.getGlobalBounds().width, m_body.getGlobalBounds().height) / 2.0f;
	}

	bool PhysicBody::CheckCollision(const PhysicBodyRef other, sf::Vector2f& direction, bool isTrigger)
	{
		if (!m_canCollide || !other->m_canCollide || IsStatic) return false;

		const sf::FloatRect myBounds = m_body.getGlobalBounds();

		//if (!myBounds.intersects(Game::m_data->window.getView().getViewport())) return false;
		
		const sf::FloatRect otherBounds = other->m_body.getGlobalBounds();

		if (!myBounds.intersects(otherBounds)) return false;

		const sf::Vector2f otherPosition = other->GetPosition();
		const sf::Vector2f otherHalfSize = other->GetHalfSize();

		float dX = otherPosition.x - m_body.getPosition().x;
		float dY = otherPosition.y - m_body.getPosition().y;

		float intersectX = std::abs(dX) - (otherHalfSize.x + GetHalfSize().x);
		float intersectY = std::abs(dY) - (otherHalfSize.y + GetHalfSize().y);

		if (intersectX >= 0.0f || intersectY >= 0.0f) return false;
		if (isTrigger) return true;

		const float restitution = 1.0f - Restitution;

		if (intersectX > intersectY)
		{
			if (dX > 0.0f)
			{
				Move({ intersectX * restitution, 0.0f });
				other->Move({ -intersectX * other->Restitution, 0.0f });

				direction = { 1.0f, 0.0f };
			}
			else
			{
				Move({ -intersectX * restitution, 0.0f });
				other->Move({ intersectX * other->Restitution, 0.0f });

				direction = { -1.0f, 0.0f };
			}
		}
		else
		{
			if (dY > 0.0f)
			{
				Move({ 0.0f, intersectY * restitution });
				other->Move({ 0.0f, -intersectY * other->Restitution });

				direction = { 0.0f, 1.0f };
			}
			else
			{
				Move({ 0.0f, -intersectY * restitution });
				other->Move({ 0.0f, intersectY * other->Restitution });

				direction = { 0.0f, -1.0f };
			}
		}
		return true;
	}

	void PhysicBody::OnCollision(sf::Vector2f direction)
	{
		if (direction.x < 0.0f)
		{
			Velocity.x = 0.0f;
		}
		else if (direction.x > 0.0f)
		{
			Velocity.x = 0.0f;
		}
		if (direction.y < 0.0f)
		{
			Velocity.y = 0.0f;
		}
		else if (direction.y > 0.0f)
		{
			IsOnGround = true;
			Velocity.y = 0.0f;
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