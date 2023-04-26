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

		m_shape.setPosition(sf::Vector2f(x, y));
		m_shape.setSize(sf::Vector2f(width, height));
		m_shape.setFillColor(containerColor);
		m_shape.setOutlineThickness(1.f);
		m_shape.setOutlineColor(outlineIdleColor);

		m_font = font;
		m_text.setFont(*m_font);
		m_text.setString(text);
		m_text.setFillColor(m_textIdleColor);
		m_text.setCharacterSize(characterSize);
		m_text.setOrigin(round(m_text.getGlobalBounds().width / 2.f + m_text.getGlobalBounds().left), round(m_text.getGlobalBounds().height / 2.f + m_text.getGlobalBounds().top));
		m_text.setPosition(
			m_shape.getPosition().x + m_shape.getGlobalBounds().width / 2.f,
			m_shape.getPosition().y + m_shape.getGlobalBounds().height / 2.f
		);

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

	void UIText::SetText(const std::string text)
	{
		m_text.setString(text);
	}
	// #### Modifiers #### //

	// #### Functions #### //
	void UIText::Draw(sf::RenderTarget& target)
	{
		target.draw(m_shape);
		target.draw(m_text);
	}
	// #### Functions #### //
}