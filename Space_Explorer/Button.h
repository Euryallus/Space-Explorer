#ifndef BUTTON_H
#define BUTTON_H

#include "SFML/Graphics.hpp"
#include "EntityData.h"
#include "TextObject.h"

//UI class used as visual representation of a "button" - use .checkIntersection() to see if mouse is over button
class Button 	
{
private:
	
	//Button components - sprite (visual rep. of button), texture from .png file, & text associated with button
	sf::Sprite m_buttonSprite;
	sf::Texture m_buttonTexture;

	TextObject text;

	

public:

	//enum values for possible colour tint (displays difficulty)
	enum class colourTint
	{
		Red,
		Orange,
		Green
	};

	//constructor
	Button( const std::string & text );
	//destructor
	~Button( );

	//checkIntersection: returns true if co-ords passed lie over the button
	bool checkIntersection( const sf::Vector2i & mouseCoords );

	//draw: runs window.draw functions for all drawable components (e.g. sprite, text)
	void draw( sf::RenderWindow & window );

	//setPosition: moves all components to position passed
	void setPosition( const sf::Vector2f & pos );

	//setButtonScale: keeps w/h ratio & scales all components by [scale] amount
	void setButtonScale( float scale );

	void tint( Button::colourTint tint );
};

#endif //BUTTON_H

