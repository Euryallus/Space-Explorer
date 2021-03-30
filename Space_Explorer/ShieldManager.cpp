#include "ShieldManager.h"
#include "ProjectileManager.h"

//manages shield objects
ShieldManager::ShieldManager( )
{
}

ShieldManager::~ShieldManager( )
{
}

//initialises all shield objects
void ShieldManager::initialise( const sf::Vector2f & screenDimensions )
{
	//indicator of current index in shield array
	int count = 0;
	//saves screen dimensions
	m_screenDimensions = screenDimensions;

	//start pos of first shield
	sf::Vector2f initialPos = sf::Vector2f( m_screenDimensions.x * 0.2f, m_screenDimensions.y * 0.75 );

	//cycles each "batch" of shields, rows & columns of each shield
	for (size_t i = 0; i < m_numberOfShields; i++) 
	{//4 "shields"

		for (size_t x = 0; x < m_xPerShield; x++) 
		{//rows of shield "pieces"

			for (size_t y = 0; y < m_yPerShield; y++)
			{//columns of shield "pieces"
				
				//initialises shield "piece" to pos. defined by values of [i], [x] and [y]
				m_shieldArray[ count ].initialise( sf::Vector2f( initialPos.x + ( i * m_spaceBetweenShields ) + x * 25, initialPos.y + y * 25 ) );
				
				//sets all shield segments to true
				m_shieldArray[ count ].setActive( true );

				//increments count
				++count;
			}
		}
	}
}

//takes ref. to projectileManager
void ShieldManager::checkCollisions( ProjectileManager & pjManager )
{
	//cycles each shield piece
	for (size_t i = 0; i < m_xPerShield * m_yPerShield * m_numberOfShields; i++) //for each shield segment
	{
		//checks if it's active & calls collision func.
		if (m_shieldArray[ i ].getActive( ) && pjManager.checkShieldCollisions( m_shieldArray[ i ] ))
		{
			//take damage if proj. is active & collision func. returns true
			m_shieldArray[ i ].takeDamage( ); 
		}
	}
}

//draws shield segments
void ShieldManager::draw( sf::RenderWindow & window ) //calls draw for every active shield segment
{
	//cycles all shield pieces
	for (size_t i = 0; i < m_xPerShield * m_yPerShield * m_numberOfShields; i++)
	{
		if (m_shieldArray[ i ].getActive( ))
		{
			//if piece is active, draw it
			window.draw( m_shieldArray[ i ] );
		}
	}
}