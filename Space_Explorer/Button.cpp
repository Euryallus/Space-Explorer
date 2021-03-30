#include <string>
#include "Button.h"

//UI class used as visual representation of a "button" - use .checkIntersection() to see if mouse is over button
Button::Button( const std::string & buttonText )
{
	//attempts to load button texture from file
	if (!m_buttonTexture.loadFromFile( "button_s.png" ))
	{
		//error
	}

	//assigns newly-loaded texture to sprite component (tiling set to false)
	m_buttonSprite.setTexture( m_buttonTexture, false );
	//sets texture "rect" to the top half of the texture, the half that contains the "off" button graphic
	m_buttonSprite.setTextureRect( sf::IntRect( 0, 0, m_buttonTexture.getSize( ).x, m_buttonTexture.getSize( ).y / ( 2 ) ) );

	//sets origin to be at the centre of the button
	m_buttonSprite.setOrigin( m_buttonSprite.getLocalBounds( ).width / 2, m_buttonSprite.getLocalBounds( ).height / 2 );

	//sets up text component (sets character size, text, colour etc.)
	text.setText( buttonText );
	text.setCharacterSize( 30 );
	text.setFillColor( sf::Color::Red );
	text.setPosition( m_buttonSprite.getOrigin( ) );
}

//deconstructor
Button::~Button( )
{
}


bool Button::checkIntersection( const sf::Vector2i & mouseCoords )
{
	//takes mouse co-ordinates as input from UIManager, uses .contains to check if mouse is over the button sprite
	bool intersects = m_buttonSprite.getGlobalBounds( ).contains( sf::Vector2f(static_cast<float>(mouseCoords.x), static_cast< float >( mouseCoords.y ) ));

	if (intersects) //if the mouse is intersecting, change the textureRect to reflect that (top 1/2 shows when button isn't hovered over, bottom 1/2 shows when button IS hovered over)
	{
		m_buttonSprite.setTextureRect(  sf::IntRect( 0, 0 , m_buttonTexture.getSize( ).x, m_buttonTexture.getSize( ).y / ( 2 ) ) );
	}
	else
	{
		m_buttonSprite.setTextureRect( sf::IntRect( 0, m_buttonTexture.getSize( ).y/ ( 2 ), m_buttonTexture.getSize( ).x, m_buttonTexture.getSize( ).y / ( 2 ) ) );
	}

	//returns value of intersects
	return intersects;
}

void Button::draw( sf::RenderWindow & window )
{
	//draws sprite and text components to the window using the ref. to the RenderWindow passed in params
	window.draw( m_buttonSprite );
	window.draw( text );
}

void Button::setPosition( const sf::Vector2f & pos )
{
	//sets position of both button sprite & text component
	m_buttonSprite.setPosition( pos );
	text.setPosition( pos );
}

void Button::setButtonScale( float scale )
{
	//takes a desired scale, scales sprite by [x] amount on both x and y axis
	m_buttonSprite.setScale( sf::Vector2f( scale, scale ) );
	//scales text size by same amount
	text.setCharacterSize( text.getCharacterSize( ) * scale );

	//resets text origin to be at centre of text (changed when character size was changed)
	text.resetOrigin( );
	//sets position of text to be back at centre of button
	text.setPosition( sf::Vector2f( m_buttonSprite.getGlobalBounds( ).left + ( m_buttonSprite.getGlobalBounds( ).width / 2 ), m_buttonSprite.getGlobalBounds( ).top + ( m_buttonSprite.getGlobalBounds( ).height / 2 )));

}

void Button::tint( Button::colourTint tint )
{
	switch (tint)
	{
	case Button::colourTint::Red:
		m_buttonSprite.setColor( sf::Color(255,102,102,255 ));
		break;
	case Button::colourTint::Orange:
		m_buttonSprite.setColor( sf::Color( 255, 255, 102, 255 ) );
		break;
	case Button::colourTint::Green:
		m_buttonSprite.setColor( sf::Color( 153, 255, 102, 255 ) );
		break;
	default:
		break;
	}
}

