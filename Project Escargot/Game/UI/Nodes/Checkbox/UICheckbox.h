#pragma once

namespace Snail
{
	namespace UI
	{
		class UICheckbox
			: public UIButton
		{
		private:
			// #### Variables #### //
			bool m_checked;	// If chackbox is checked
			std::string m_falseStateText;	// Text for false state
			std::string m_trueStateText;	// Text for true state
			// #### Variables #### //
		public:
			// #### Constructor | Destructor #### //
			UICheckbox(float x, float y, float width, float height,
				sf::Font* font, unsigned characterSize,
				sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
				sf::Color containerIdleColor, sf::Color hoverColor, sf::Color activeColor,
				sf::Color outlineIdleColor = sf::Color::Transparent,
				sf::Color outlineHoverColor = sf::Color::Transparent,
				sf::Color outlineActiveColor = sf::Color::Transparent,
				short unsigned id = 0);		// Class constructor (textStates : {falseStateText, trueStateText})
			~UICheckbox();
			// #### Constructor | Destructor #### //

			// #### Modifiers #### //
			void SwitchState();
			// #### Modifiers #### //

			// #### Accessors #### //
			const bool IsChecked() const;
			// #### Accessors #### //

			// #### Functions #### //

			// #### Functions #### //
		};
	}
}