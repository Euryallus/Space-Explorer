#include "Entity.h"
#include "ProjectileManager.h"
#include "Projectile.h"
#include "EnemyManager.h"
#include "Player.h"
#include "Game.h"
#include "DifficultyData.h"
#include "Shield.h"
#include "SFML/Graphics.hpp"

//manages projectiles.
ProjectileManager::ProjectileManager( )
{
	//sets projectile pointers to 0 on creation
	m_player1Pointer = 0;
	m_enemyPointer = 0;
}

ProjectileManager::~ProjectileManager( )
{
	//sets EnemyManager pointer to null
	m_enemyManager = nullptr;
}

void ProjectileManager::assignEnemyManager( EnemyManager * enemyManager )
{
	//initialise - assign EnemyManager pointer & set difficulty-dependant values to default
	m_enemyManager = enemyManager;
	m_maxPlayerShots = difficulty::playerBulletCount[ static_cast< int >( difficulty::currentDifficultyEnum ) ];
	m_enemyProjectileSpeed = difficulty::enemyProjSpeed[ static_cast< int >( difficulty::currentDifficultyEnum ) ];
	m_enemySpeedIncrease = difficulty::enemySpeedIncrease[ static_cast< int >( difficulty::currentDifficultyEnum ) ];
}

void ProjectileManager::spawnPlayerProjectile( const sf::Vector2f & position )
{
	//cycles all "possible" bullets, checks if one is inactive
	for (size_t i = 0; i < m_maxPlayerShots; i++)
	{
		if (!m_player1Projectiles[ i ].getActive( ))
		{
			//if finds inactive bullet, initialises bullet (sets position, direction, speed etc.)
			m_player1Projectiles[ i ].initialise( position );
			m_player1Projectiles[ i ].setDirection( EntityData::entityDirections::up );
			m_player1Projectiles[ i ].setActive( true );
								  
			m_player1Projectiles[ i ].setSpeed( 600.f );
			//plays shooting sound
			shootSFX.play( ); 
			break;
		}
	}

}

void ProjectileManager::spawnEnemyProjectile( const sf::Vector2f & position ) //spawns projecile at pos given
{
	//creates enemy bullet at position passed by EnemyManager and sets direction, speed, active status etc.
	m_enemyProjeciles[ m_enemyPointer ].initialise( position );
	m_enemyProjeciles[ m_enemyPointer ].setDirection( EntityData::entityDirections::down );

	m_enemyProjeciles[ m_enemyPointer ].setSpeed( m_enemyProjectileSpeed );
	m_enemyProjeciles[ m_enemyPointer ].setActive( true );

	//cycles enemy array (allows up to 20 bullets to be active at once)
	m_enemyPointer == 19 ? m_enemyPointer = 0 : ++m_enemyPointer; 
	//plays shoot sound
	shootSFX.play( ); //play sfx
}

void ProjectileManager::checkEnemyCollisions( ) //takes enemyManager
{
	for (size_t i = 0; i < 20; i++) //for each projectile in player list
	{
		if (m_player1Projectiles[ i ].getActive( ) && m_enemyManager->checkEnemyProjectileCollisions( m_player1Projectiles[ i ] ))
		{
			m_player1Projectiles[ i ].setActive( false ); //if projectile collides with an enemy, set state to disabled
			m_enemyManager->increaseSpeed( m_enemySpeedIncrease ); //increase enemy speed
		}

		if (m_player1Projectiles[ i ].getActive( ) && m_player1Projectiles[ i ].getPosition( ).y <= 80) //disables player projectiles that reach top of screen
		{
			m_player1Projectiles[ i ].setActive( false );
		}
	}
}

bool ProjectileManager::checkShieldCollisions( Shield & shield ) //takes shield segment as param
{
	for (size_t i = 0; i < 20; i++) //for each projectile for p1, p2 & enemies
	{
		if (m_enemyProjeciles[ i ].getGlobalBounds( ).intersects( shield.getGlobalBounds( ) ) && m_enemyProjeciles[ i ].getActive( ))
		{
			//checks if projectile collides w/ shield piece, if true disable projectile & return true
			m_enemyProjeciles[ i ].setActive( false ); 
			spawnEnemyProjectile( m_enemyManager->enemyShoot( ) ); //spawns new enemy projectile at position passed by enemymanager
			return true;
		}

		// checks if projectile collides w / shield piece, if true disable projectile & return true
		if (m_player1Projectiles[ i ].getGlobalBounds( ).intersects( shield.getGlobalBounds( ) ) && m_player1Projectiles[ i ].getActive( ))
		{
			m_player1Projectiles[ i ].setActive( false );
			return true;
		}
	}
	//return false if doesnt collide
	return false; 
}

//check enemy projectile against player
void ProjectileManager::checkPlayerCollisions( Player & player )
{
	//cycles each enemy projectile
	for (size_t i = 0; i < 20; i++)
	{
		if (m_enemyProjeciles[ i ].getActive( ))
		{
			//if collides w/ player & is active - disable projectile, player takes damage, spawn new enemy projectile
			if (player.checkCollision( m_enemyProjeciles[ i ] ))
			{
				m_enemyProjeciles[ i ].setActive( false );
				m_playerHurt.play( );
				player.takeDamage( 1 );
				spawnEnemyProjectile( m_enemyManager->enemyShoot( ) );
			}

			//checks Y co-ord of projectile (if over 900 it's reached bottom of screen, disable it and spawn new one)
			else if (m_enemyProjeciles[ i ].getPosition( ).y > 825)
			{
				m_enemyProjeciles[ i ].setActive( false );
				spawnEnemyProjectile( m_enemyManager->enemyShoot( ) );
			}
		}
	}
}

//updates each projectile
void ProjectileManager::updateProjectiles( Player & player, float deltaTime ) //if each projectile is active, update (e.g. move)
{
	for (size_t i = 0; i < 20; i++)
	{
		if (m_player1Projectiles[ i ].getActive( )) //updates player projectile if it's active
		{
			m_player1Projectiles[ i ].update( deltaTime );
		}

		if (m_enemyProjeciles[ i ].getActive( )) //updates enemy projectile if it's active
		{
			m_enemyProjeciles[ i ].update( deltaTime );
		}
	}

	//call enemy collision detection
	checkEnemyCollisions( ); 
	//call player collision detection
	checkPlayerCollisions( player ); 
}

//calls draw function on all active projectiles
void ProjectileManager::drawProjectiles( sf::RenderWindow & window ) 
{
	for (size_t i = 0; i < 20; i++)
	{
		//if projectile is active, draw it
		if (m_player1Projectiles[ i ].getActive( )) 
		{
			window.draw( m_player1Projectiles[ i ] );
		}

		if (m_enemyProjeciles[ i ].getActive( ))
		{
			window.draw( m_enemyProjeciles[ i ] );
		}
	}
}

void ProjectileManager::reset( )
{
	//sets each bullet as inactive
	for (size_t i = 0; i < 20; i++)
	{
		m_enemyProjeciles[ i ].setActive( false );
	}

	//re-defines difficulty-based variables
	m_enemyProjectileSpeed = difficulty::enemyProjSpeed [ static_cast<int>(difficulty::currentDifficultyEnum) ];
	m_maxPlayerShots = difficulty::playerBulletCount [ static_cast< int >( difficulty::currentDifficultyEnum ) ];
	m_enemySpeedIncrease = difficulty::enemySpeedIncrease[ static_cast< int >( difficulty::currentDifficultyEnum ) ];

}
