#ifndef TEXTOBJECT_H
#define TEXTOBJECT_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

#include <string>

//text obj class, inherits from Text (allows font & text associated w/ it to be stored as contained object)
class TextObject
	: public sf::Text
{
private:
	//stores font associated with text in game (like a texture, but for text)
	sf::Font m_font;

public:
	//constructor
	TextObject( );
	//destructor
	~TextObject( );

	//sets text to string passed
	void setText( const std::string & text );
	//recalculates origin to be at centre of object
	void resetOrigin( );
};

#endif