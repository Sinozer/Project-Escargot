#include "stdafx.h"
#include "UIText.h"
namespace Snail
{
	// #### Constructor | Destructor #### //
	UIText::UIText(float x, float y, float width, float height,
		sf::Font* font, std::string text, unsigned characterSize,
		sf::Color textColor, sf::Color containerColor, sf::Color outlineIdleColor)
	{
		m_origin = TOP_LEFT;

		m_textIdleColor = textColor;
		m_containerIdleColor = containerColor;
		m_outlineIdleColor = outlineIdleColor;

		m_position = sf::Vector2f(x, y);

		m_shape.setPosition(sf::Vector2f(x, y));
		m_shape.setFillColor(containerColor);
		m_shape.setOutlineThickness(1.f);
		m_shape.setOutlineColor(outlineIdleColor);

		m_font = font;
		m_text.setFont(*m_font);
		m_text.setString(text);
		m_text.setFillColor(m_textIdleColor);
		m_text.setCharacterSize(characterSize);
		m_text.setOrigin(round(m_text.getGlobalBounds().width / 2.f + m_text.getGlobalBounds().left), round(m_text.getGlobalBounds().height / 2.f + m_text.getGlobalBounds().top));

		if (width <= 0.f && height <= 0.f)
			m_shape.setSize(sf::Vector2f(m_text.getGlobalBounds().width * 1.2f, m_text.getGlobalBounds().height * 1.2f));
		else
			m_shape.setSize(sf::Vector2f(width, height));

		m_shape.setOrigin(round(m_shape.getGlobalBounds().width / 2.f), round(m_shape.getGlobalBounds().height / 2.f));
		m_text.setPosition(x, y);
	}

	UIText::~UIText()
	{
		//delete font;
	}
	// #### Constructor | Destructor #### //

	// #### Accessors #### //
	const std::string UIText::GetText() const
	{
		return m_text.getString();
	}
	const sf::Vector2f UIText::GetPosition(Origin origin) const
	{
		sf::Vector2f position = sf::Vector2f(m_shape.getGlobalBounds().left, m_shape.getGlobalBounds().top);

		switch (origin)
		{
		case Snail::TOP_LEFT:
			break;
		case Snail::TOP_MID:
			position.x += m_shape.getGlobalBounds().width / 2.f;
			break;
		case Snail::TOP_RIGHT:
			position.x += m_shape.getGlobalBounds().width;
			break;
		case Snail::MID_LEFT:
			position.y += m_shape.getGlobalBounds().height / 2.f;
			break;
		case Snail::MID_MID:
			position.x += m_shape.getGlobalBounds().width / 2.f;
			position.y += m_shape.getGlobalBounds().height / 2.f;
			break;
		case Snail::MID_RIGHT:
			position.x += m_shape.getGlobalBounds().width;
			position.y += m_shape.getGlobalBounds().height / 2.f;
			break;
		case Snail::BOT_LEFT:
			position.y += m_shape.getGlobalBounds().height;
			break;
		case Snail::BOT_MID:
			position.x += m_shape.getGlobalBounds().width / 2.f;
			position.y += m_shape.getGlobalBounds().height;
			break;
		case Snail::BOT_RIGHT:
			position.x += m_shape.getGlobalBounds().width;
			position.y += m_shape.getGlobalBounds().height;
			break;
		}

		return position;
	}
	// #### Accessors #### //

	// #### Modifiers #### //


	void UIText::SetOrigin(Origin origin)
	{
		m_origin = origin;

		switch (origin)
		{
		case TOP_LEFT:
			m_shape.setOrigin(0.f, 0.f);
			break;
		case TOP_MID:
			m_shape.setOrigin(round(m_shape.getGlobalBounds().width / 2.f), 0.f);
			break;
		case TOP_RIGHT:
			m_shape.setOrigin(m_shape.getGlobalBounds().width, 0.f);
			break;
		case MID_LEFT:
			m_shape.setOrigin(0.f, round(m_shape.getGlobalBounds().height / 2.f));
			break;
		case MID_MID:
			m_shape.setOrigin(round(m_shape.getGlobalBounds().width / 2.f), round(m_shape.getGlobalBounds().height / 2.f));
			break;
		case MID_RIGHT:
			m_shape.setOrigin(m_shape.getGlobalBounds().width, round(m_shape.getGlobalBounds().height / 2.f));
			break;
		case BOT_LEFT:
			m_shape.setOrigin(0.f, m_shape.getGlobalBounds().height);
			break;
		case BOT_MID:
			m_shape.setOrigin(round(m_shape.getGlobalBounds().width / 2.f), m_shape.getGlobalBounds().height);
			break;
		case BOT_RIGHT:
			m_shape.setOrigin(m_shape.getGlobalBounds().width, m_shape.getGlobalBounds().height);
			break;
		default:
			break;
		}

		SetPosition(m_position);

	}

	void UIText::SetPosition(sf::Vector2f position)
	{
		m_position = position;
		m_shape.setPosition(position);
		m_text.setPosition(m_shape.getGlobalBounds().left + m_shape.getGlobalBounds().width / 2.f, m_shape.getGlobalBounds().top + m_shape.getGlobalBounds().height / 2.f);
	}

	void UIText::SetText(const std::string text)
	{
		m_text.setString(text);
		sf::Vector2f origin = sf::Vector2f(round(m_text.getGlobalBounds().width / 2.f), round(m_text.getGlobalBounds().height / 2.f));
		m_text.setOrigin(origin);

		m_shape.setSize(sf::Vector2f(m_text.getGlobalBounds().width * 1.2f, m_text.getGlobalBounds().height * 1.2f));
		SetOrigin(m_origin);
		SetPosition(m_position);
	}

	void UIText::SetTextColor(sf::Color color)
	{
		m_text.setFillColor(color);
	}

	void UIText::SetFontSize(unsigned int size)
	{
		m_text.setCharacterSize(size);
	}

	void UIText::SetOutlineColor(sf::Color color)
	{
		m_text.setOutlineColor(color);
	}

	void UIText::SetOutlineThickness(float thickness)
	{
		m_text.setOutlineThickness(thickness);
	}
	// #### Modifiers #### //

	// #### Functions #### //
	void UIText::Draw(sf::RenderTarget& target)
	{
		if (!IsActive) return;
		target.draw(m_shape);
		target.draw(m_text);
	}
	// #### Functions #### //
}