#include "TextObject.h"

//text object, compacted to contain text AND font data
TextObject::TextObject( )
	: sf::Text( )
{
	//attempts to load default font
	if (!m_font.loadFromFile( "Spaceport_2006.otf" ))
	{
		//failed
	}
	//assigns font to Text
	setFont( m_font );

	//sets string component to blank, sets colour to black
	setString( "" );
	setFillColor( sf::Color( 0, 0, 0, 255 ) );
}

TextObject::~TextObject( )
{
}

//allows text to be changed
void TextObject::setText( const std::string & text )
{
	//assigns text passed as string component
	setString( text );
	//alters origin to be at centre of text
	setOrigin( sf::Vector2f( getLocalBounds( ).width / 2, getLocalBounds( ).height / 2 ) );
}

void TextObject::resetOrigin( )
{
	//alters origin to be at centre of text
	setOrigin( sf::Vector2f( getLocalBounds( ).width / 2, getLocalBounds( ).height / 2 ) );
}