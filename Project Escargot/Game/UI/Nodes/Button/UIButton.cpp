#include "stdafx.h"
#include "UIButton.h"

// #### Constructor | Destructor #### //
Snail::UI::UIButton::UIButton(float x, float y, float width, float height,
	sf::Font* font, std::string text, unsigned characterSize,
	sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
	sf::Color containerIdleColor, sf::Color hoverColor, sf::Color activeColor,
	sf::Color outlineIdleColor, sf::Color outlineHoverColor, sf::Color outlineActiveColor,
	short unsigned id)
	: UIText(x, y, width, height, font, text, characterSize, textIdleColor, containerIdleColor, outlineIdleColor)
{
	m_keyTimeMax = 1.f;
	m_keyTime = 0.f;

	m_state = IDLE;
	m_id = id;

	m_textHoverColor = textHoverColor;
	m_textActiveColor = textActiveColor;

	m_hoverColor = hoverColor;
	m_activeColor = activeColor;

	m_outlineHoverColor = outlineHoverColor;
	m_outlineActiveColor = outlineActiveColor;
}

Snail::UI::UIButton::~UIButton()
{

}
// #### Constructor | Destructor #### //

// #### Accessors #### //
const bool Snail::UI::UIButton::GetKeyTime()
{
	if (m_keyTime >= m_keyTimeMax)
	{
		m_keyTime = 0.f;
		return true;
	}
	return false;
}

const bool Snail::UI::UIButton::IsPressed() const
{
	if (m_state == ACTIVE)
		return true;
	return false;
}

const short unsigned& Snail::UI::UIButton::GetId() const
{
	return m_id;
}
// #### Accessors #### //

// #### Modifiers #### //
void Snail::UI::UIButton::UpdateKeyTime(const float& dt)
{
	if (m_keyTime < m_keyTimeMax)
		m_keyTime += 5.f * dt;
}

void Snail::UI::UIButton::SetId(const short unsigned id)
{
	m_id = id;
}
// #### Modifiers #### //

// #### Functions #### //
void Snail::UI::UIButton::Update(const float& dt)
{
	UpdateKeyTime(dt);


	m_state = IDLE;	// Idle

	//if (m_shape.getGlobalBounds().contains(/*Get mouse pos from input controller*/))	// Hover
	//{
	//	m_state = HOVER;

	//	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && GetKeyTime())	// Active
	//	{
	//		m_state = ACTIVE;
	//	}
	//}

	switch (m_state)
	{
	case IDLE:
		m_shape.setFillColor(m_containerIdleColor);
		m_text.setFillColor(m_textIdleColor);
		m_shape.setOutlineColor(m_outlineIdleColor);
		break;
	case HOVER:
		m_shape.setFillColor(m_hoverColor);
		m_text.setFillColor(m_textHoverColor);
		m_shape.setOutlineColor(m_outlineHoverColor);
		break;
	case ACTIVE:
		m_shape.setFillColor(m_activeColor);
		m_text.setFillColor(m_textActiveColor);
		m_shape.setOutlineColor(m_outlineActiveColor);
		break;
	default:
		m_shape.setFillColor(sf::Color::Red);
		m_text.setFillColor(sf::Color::Blue);
		m_shape.setOutlineColor(sf::Color::Green);
		break;
	}
}
// #### Functions #### //