#pragma once
#include "Game/UI/Nodes/Text/UIText.h"
namespace Snail
{
	enum UIState { IDLE = 0, HOVER, ACTIVE };
	
	class UIButton
		: public UIText
	{
	protected:
		// #### Variables #### //
		float m_keyTime;
		float m_keyTimeMax;

		short unsigned m_previousState;
		short unsigned m_state;
		short unsigned m_id;

		sf::Color m_textHoverColor;
		sf::Color m_textActiveColor;

		sf::Color m_hoverColor;
		sf::Color m_activeColor;

		sf::Color m_outlineHoverColor;
		sf::Color m_outlineActiveColor;
		// #### Variables #### //
	public:
		// #### Constructor | Destructor #### //
		UIButton(float x, float y, float width, float height,
			sf::Font* font, std::string text, unsigned characterSize,
			sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
			sf::Color containerIdleColor, sf::Color hoverColor, sf::Color activeColor,
			sf::Color outlineIdleColor = sf::Color::Transparent,
			sf::Color outlineHoverColor = sf::Color::Transparent,
			sf::Color outlineActiveColor = sf::Color::Transparent,
			short unsigned id = 0);		// Class constructor
		~UIButton();				// Class destructor
		// #### Constructor | Destructor #### //

		// #### Accessors #### //
		const bool GetKeyTime();
		const bool IsPressed() const;
		const short unsigned& GetId() const;
		// #### Accessors #### //

		// #### Modifiers #### //
		void UpdateKeyTime();
		void SetId(const short unsigned id);
		// #### Modifiers #### //

		// #### Functions #### //
		void Update();	// Update booleans for hover and pressed
		// #### Functions #### //
	};
}