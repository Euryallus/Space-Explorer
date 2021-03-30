#include "Player.h"
#include "Projectile.h"

#include "SoundClip.h"

//player class, inherrits from Entity (default 1 frame (non animated))
Player::Player( )
	: Entity( 1 )
{
}

Player::Player( EntityData::entityTextures texture )
	: Entity( texture , 1)
{
}

//overridden func. from Entity - resets player to default pos. with [x] lives & health
void Player::initialise( const sf::Vector2f & maxPos, int maxLives, int maxHealth )
{
	//health data stored
	m_maxHealth = maxHealth;
	m_maxLives = maxLives;
	m_health = m_maxHealth;
	m_lives = m_maxLives;


	//sets speed
	m_speed = 200.f;

	m_screenDimensions = maxPos;

	//runs base initialise function
	Entity::initialise( sf::Vector2f( maxPos.x / 2, maxPos.y * 0.85f ) );

}

//destructor
Player::~Player( )
{
}

//overridden func. from Entity
void Player::update( float deltaTime )
{
	//saves position at start of frame
	sf::Vector2f pos = getPosition( );
	//stores delta time
	m_deltaTime = deltaTime;

	//takes kepboard input - sets direction & rotation of player
	if (sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) || sf::Keyboard::isKeyPressed( sf::Keyboard::A ))
	{
		setDirection( EntityData::entityDirections::left );
		setRotation( -5.f );
	}
	else if (sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) || sf::Keyboard::isKeyPressed( sf::Keyboard::D ))
	{
		setDirection( EntityData::entityDirections::right );
		setRotation( 5.f );
	}

	//if no input specified, "direction" is 0,0 (stationary
	else
	{
		setDirection( EntityData::entityDirections::stationary );
		setRotation( 0.f );
	}

	//calls move func
	move( );

	if (!(getPosition( ).x > m_screenDimensions.x * 0.1f && getPosition( ).x < m_screenDimensions.x * 0.9f))
	{
		//if move() caused pos. to be over bountries, reset pos. to position saved from start of frame
		setPosition( pos );
	}

	//checks if player has been hit within the last second - if so, adjust colour 
	if (m_hasBeenHit)
	{
		//player flashes red when hit, lerps from red to white tint over 1 second
		m_damageColourEffect += 255 * deltaTime;
		
		setColor( sf::Color( 255, m_damageColourEffect, m_damageColourEffect, 255 ) );

		//if colour is close enough to white (255, 255, 255) flag m_hasBeenHit to false & set colour to white
		if (m_damageColourEffect >= 250)
		{
			m_hasBeenHit = false;
			setColor( sf::Color( 255, 255, 255, 255 ) );
		}
	}
}

//returns bool
bool Player::checkCollision( Entity object )
{
	//returns true / false based on whether object passed intersects with self
	return getGlobalBounds( ).intersects( object.getGlobalBounds( ) );
}

void Player::takeDamage( int damage )
{
	//decrements health by amount specified
	m_health -= damage;
	//initialises colour flash (red)
	setColor( sf::Color( 255, 0, 0, 255 ) );
	m_damageColourEffect = 0;
	m_hasBeenHit = true;

	//if health is 0, reduce lives by 1 and resets health to maxHealth
	if (m_health == 0) 
	{
		m_lives -= 1;

		if (m_lives == 0) //if run out of lives, player is deactivated
		{
			m_isActive = false;
		}
		else
		{
			m_health = m_maxHealth;
		}
	}
}

int Player::returnLives( )
{
	//returns lives int (used by UIManager)
	return m_lives;
}

int Player::returnMaxLives( )
{
	//returns max lives int (used by UIManager)
	return m_maxLives;
}