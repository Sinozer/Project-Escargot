#pragma once

namespace Snail
{
	class UIText
	{
	protected:
		// #### Variables #### //
		sf::RectangleShape m_shape;
		sf::Font* m_font;
		sf::Text m_text;

		sf::Color m_textIdleColor;

		sf::Color m_containerIdleColor;

		sf::Color m_outlineIdleColor;
		// #### Variables #### //
	public:
		// #### Constructor | Destructor #### //
		UIText(float x, float y, float width, float height,
			sf::Font* font, std::string text, unsigned characterSize,
			sf::Color textColor, sf::Color containerColor,
			sf::Color outlineColor = sf::Color::Transparent);		// Class constructor
		~UIText();				// Class destructor
		// #### Constructor | Destructor #### //

		// #### Accessors #### //
		const std::string GetText() const;
		// #### Accessors #### //

		// #### Modifiers #### //
		void SetText(const std::string text);
		// #### Modifiers #### //

		// #### Functions #### //
		void Draw(sf::RenderTarget& target);
		// #### Functions #### //
	};
}