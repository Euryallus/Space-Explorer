#ifndef SHIELD_H
#define SHIELD_H
#include <SFML/Graphics.hpp>
#include "Entity.h"

//Shield object, inherits from Entity
class Shield
	: public Entity
{
private:
	//used to store current texture of shield object
	sf::Texture m_shieldTexture;
	//dictionary of texture file names / remaining health (e.g. 3 is mapped to "shield3Health.png")
	std::map <int, sf::String> m_textureMap;

public:
	//default constructor
	Shield();
	//destructor
	~Shield();

	//overridden initialise func. from Entity, sets values to default and calls base initialise func. when done
	void initialise( const sf::Vector2f & position );
	//overridden takeDamage func. from Entity, change stexture loaded for shield to reflect health remaining
	void takeDamage();
};

#endif //SHIELD_H