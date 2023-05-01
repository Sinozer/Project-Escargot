#include "stdafx.h"
#include "UIText.h"
namespace Snail
{
	// #### Constructor | Destructor #### //
	UIText::UIText(float x, float y, float width, float height,
		sf::Font* font, std::string text, unsigned characterSize,
		sf::Color textColor, sf::Color containerColor, sf::Color outlineIdleColor)
	{
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
	// #### Accessors #### //

	// #### Modifiers #### //


	void UIText::SetOrigin(Origin origin)
	{
		m_origin = origin;

		switch (origin)
		{
		case TOP_LEFT:
			m_shape.setOrigin(0.f, 0.f);
			m_text.setOrigin(0.f, 0.f);
			break;
		case TOP_MID:
			m_shape.setOrigin(round(m_shape.getGlobalBounds().width / 2.f), 0.f);
			m_text.setOrigin(round(m_text.getGlobalBounds().width / 2.f + m_text.getGlobalBounds().left), 0.f);
			break;
		case TOP_RIGHT:
			m_shape.setOrigin(m_shape.getGlobalBounds().width, 0.f);
			m_text.setOrigin(m_text.getGlobalBounds().width, 0.f);
			break;
		case MID_LEFT:
			m_shape.setOrigin(0.f, round(m_shape.getGlobalBounds().height / 2.f));
			m_text.setOrigin(0.f, round(m_text.getGlobalBounds().height / 2.f + m_text.getGlobalBounds().top));
			break;
		case MID_MID:
			m_shape.setOrigin(round(m_shape.getGlobalBounds().width / 2.f), round(m_shape.getGlobalBounds().height / 2.f));
			m_text.setOrigin(round(m_text.getGlobalBounds().width / 2.f + m_text.getGlobalBounds().left), round(m_text.getGlobalBounds().height / 2.f + m_text.getGlobalBounds().top));
			break;
		case MID_RIGHT:
			m_shape.setOrigin(m_shape.getGlobalBounds().width, round(m_shape.getGlobalBounds().height / 2.f));
			m_text.setOrigin(m_text.getGlobalBounds().width, round(m_text.getGlobalBounds().height / 2.f + m_text.getGlobalBounds().top));
			break;
		case BOT_LEFT:
			m_shape.setOrigin(0.f, m_shape.getGlobalBounds().height);
			m_text.setOrigin(0.f, m_text.getGlobalBounds().height);
			break;
		case BOT_MID:
			m_shape.setOrigin(round(m_shape.getGlobalBounds().width / 2.f), m_shape.getGlobalBounds().height);
			m_text.setOrigin(round(m_text.getGlobalBounds().width / 2.f + m_text.getGlobalBounds().left), m_text.getGlobalBounds().height);
			break;
		case BOT_RIGHT:
			m_shape.setOrigin(m_shape.getGlobalBounds().width, m_shape.getGlobalBounds().height);
			m_text.setOrigin(m_text.getGlobalBounds().width, m_text.getGlobalBounds().height);
			break;
		default:
			break;
		}

		m_text.setPosition(m_shape.getGlobalBounds().left + m_shape.getGlobalBounds().width / 2.f, m_shape.getGlobalBounds().top + m_shape.getGlobalBounds().height / 2.f);

	}

	void UIText::SetText(const std::string text)
	{
		m_text.setString(text);

		m_shape.setSize(sf::Vector2f(m_text.getGlobalBounds().width * 1.2f, m_text.getGlobalBounds().height * 1.2f));
		SetOrigin(m_origin);
		m_shape.setPosition(m_position);
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