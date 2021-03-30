#include "Shield.h"

//shield class, inherits from Entity
Shield::Shield( )
	: Entity( 1 )
{
	//calls Entity constructor, defines 1 anim. frame (not animated)
	m_isActive = false;
	//sets health to 4
	m_health = 4;

	//map of health -> texture file name
	m_textureMap[ 0 ] = "shield0Health.png"; 
	m_textureMap[ 1 ] = "shield1Health.png";
	m_textureMap[ 2 ] = "shield2Health.png";
	m_textureMap[ 3 ] = "shield3Health.png";
	m_textureMap[ 4 ] = "shield4Health.png";

	//sets texture to shield4Health (max. health)
	if (m_texture.loadFromFile( "shield4Health.png" )) 
	{ 
		//assigns texture
		setTexture( m_texture );
	}
}
Shield::~Shield( )
{
}

void Shield::initialise( const sf::Vector2f & position )
{
	//sets texture to shield4Health (max. health)
	m_health = 4;
	if (m_texture.loadFromFile( "shield4Health.png" )) 
	{
		setTexture( m_texture ); //assigns texture
	}

	//calls base initialise func from Entity
	Entity::initialise( position );
}

void Shield::takeDamage( )
{
	//decrements health
	--m_health; 

	//assigns m_texture to .png defined in m_textureMap
	if (m_texture.loadFromFile( m_textureMap[ m_health ] )) 
	{ 
		//sets texture if load was complete
		setTexture( m_texture );
	}

	if (m_health == 0)
	{
		//if health == 0, disable shield segment
		m_isActive = false; 
	}
}