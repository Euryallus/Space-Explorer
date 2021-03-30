#include <iostream>
#include "EnemyManager.h"
#include "Projectile.h"
#include "DifficultyData.h"

//manages enemies.
EnemyManager::EnemyManager( )
{
	//sets default movement direction
	m_movementDirection = EntityData::entityDirections::right;
}

//destructor
EnemyManager::~EnemyManager( )
{
	//sets pointer to null
	m_scoreManager = nullptr;
}

void EnemyManager::update( float deltaTime )
{
	//sets m_deltaTime value, calls move() func.
	m_deltaTime = deltaTime;
	move( );
}

void EnemyManager::draw( sf::RenderWindow & window )
{
	//cycles each enemy, if it's not dead it gets drawn to the screen
	for (size_t i = 0; i < m_noOfEnemies; i++)
	{
		if (m_enemyArray[ i ].returnState( ) != Enemy::EnemyStates::dead)
		{
			window.draw( m_enemyArray[ i ] );
		}
	}
}

//run when game is started / restarted, assigns values to default & "places" enemies
void EnemyManager::setUp( const sf::Vector2f & screenDimensions, ScoreManager * scoreManager )
{
	//takes number of rows from difficulty settings
	m_noOfRows = difficulty::enemyRows[ static_cast< int >( difficulty::currentDifficultyEnum ) ];
	//sets m_noOfEnemies to rows * columns (e.g. 11 columns * 4 rows = 44 enemies)
	m_noOfEnemies = m_noOfColumns * m_noOfRows;

	//saves screen dimensions (defaults to 800 x 900)
	m_screenDimensions = screenDimensions;

	//sets bools required for lose-state detection
	oneIsStillActive = true;
	hasHitBottom = false;

	//sets initial enemy speed to 25
	m_initialSpeed = 25.f;
	//sets scoreManager pointer to pointer passed as param
	m_scoreManager = scoreManager;

	//used to store [i] of next enemy in for loops below
	int count = 0;

	//cycles [x] and [y] of layout, initialises enemy 
	for (int y = 0; y < m_noOfRows; y++)
	{
		for (int x = 0; x < m_noOfColumns; x++)
		{
			//initialises array at [x] [y] position, sets speed to speed defined above, and sets texture according to row
			m_enemyArray[ count ].initialise( sf::Vector2f( m_screenDimensions.x * 0.15f + ( x * 50.f ), ( m_screenDimensions.y * 0.15f ) + ( y * 50.f ) ) );
			m_enemyArray[ count ].setSpeed( m_initialSpeed );

			m_enemyArray[ count ].setAnimRate( 0.25f );

			switch (y)
			{
			case 4:
			case 3:
				m_enemyArray[ count ].changeTexture( EntityData::entityTextures::enemy1 );
				break;

			case 2:
			case 1:
				m_enemyArray[ count ].changeTexture( EntityData::entityTextures::enemy2 );
				break;

			case 0:
				m_enemyArray[ count ].changeTexture( EntityData::entityTextures::enemy3 );
				break;

			default:
				break;
			}
			count += 1;
		}
	}

	//locates and saves the left most, right most and bottom most enemy (used to check lose state & whether enemies need to move down & turn around)
	findBufferEnemies( );

}

void EnemyManager::move( )
{
	//checks whether an enemy is still active - cycles enemy list, if 1 or more show up oneIsStillActive is flagged as true
	oneIsStillActive = false;

	for (size_t i = 0; i < m_noOfEnemies; i++)
	{
		if (m_enemyArray[ i ].returnState( ) == Enemy::EnemyStates::alive)
		{
			oneIsStillActive = true;
		}
	}

	//only runs if one enemy is still active
	//if (oneIsStillActive)
	//{
		//checks x location of right-most enemy - if it's hit the right buffer & it's been travelling in the right direction, move down
		if (m_enemyArray[ rightMostI ].getPosition( ).x > m_screenDimensions.x * 0.9f)
		{
			if (m_movementDirection == EntityData::entityDirections::right)
			{
				m_movementDirection = EntityData::entityDirections::downLarge;
			}
			else //if it's already moved down (2nd time this check is hit), start moving left
			{
				m_movementDirection = EntityData::entityDirections::left;
			}
		}
		//checks x location of left-most enemy - if it's hit the left buffer & it's been travelling in the left direction, move down
		if (m_enemyArray[ leftMostI ].getPosition( ).x < m_screenDimensions.x * 0.1f)
		{
			if (m_movementDirection == EntityData::entityDirections::left)
			{
				m_movementDirection = EntityData::entityDirections::downLarge;
			}
			else //if it's already moved down (2nd time this check is hit), start moving right
			{
				m_movementDirection = EntityData::entityDirections::right;
			}
		}

		//checks y location of bottom-most enemy - if it's below the shields, flag hasHitBottom as true
		if (m_enemyArray[ bottomMostI ].getPosition( ).y > m_screenDimensions.y * 0.8)
		{
			hasHitBottom = true;
		}

		//calls update for all active enemies and assigns correct movement direction
		for (size_t i = 0; i < m_noOfEnemies; i++)
		{
			if (m_enemyArray[ i ].getActive( ))
			{
				m_enemyArray[ i ].setDirection( m_movementDirection );

				m_enemyArray[ i ].update( m_deltaTime );
			}
		}
	//}
	//else
	//{
	//	//no enemies are alive, will get picked up in Game
	//}
}

bool EnemyManager::checkEnemyProjectileCollisions( const Projectile & proj )
{
	//cycles each active enemy
	for (size_t i = 0; i < m_noOfEnemies; i++)
	{
		//if the projectile passed intersects with the enemy at [i], return true, update score, and make enemy take damage
		if (proj.getGlobalBounds( ).intersects( m_enemyArray[ i ].getGlobalBounds( ) ) && m_enemyArray[ i ].returnState( ) == Enemy::EnemyStates::alive)
		{
			m_enemyArray[ i ].takeDamage( 1 );
			m_scoreManager->updateCurrentScore(	difficulty::enemyScoreIncrease[static_cast<int>(difficulty::currentDifficultyEnum)] );

			findBufferEnemies( );

			return true;
		}
	}
	//if proj. doesn't collide with any enemies, return false
	return false;
}

//called by ProjectileManager when previous enemy shot is deactivated OR "round" starts
sf::Vector2f EnemyManager::enemyShoot( )
{
	//checks if an enemy is still alive
	if (oneIsStillActive)
	{
		//generates a random [i] between 0 and (m_noOfEnemies - 1)
		int enemyToShoot = rand( ) % m_noOfEnemies;

		//if the random enemy selected isn't alive, pick a new one until they are alive
		while (!( m_enemyArray[ enemyToShoot ].returnState( ) == Enemy::EnemyStates::alive ))
		{
			enemyToShoot = rand( ) % m_noOfEnemies;
		}

		//returns co-ords of random alive enemy chosen to shoot bullet
		return m_enemyArray[ enemyToShoot ].getPosition( );
	}
	else //if func. was called when no enemies are still alive, return off-screen co-ords (will only be hit if func. is called by mistake)
	{
		return sf::Vector2f( 999, 999 );
	}
}

//increases speed by amount specified, used when an enemy dies
void EnemyManager::increaseSpeed( float increaseAmount )
{
	//increments m_initialSpeed by amount passed
	m_initialSpeed = m_initialSpeed + increaseAmount;

	//assigns new speed val to all enemies in array
	for (size_t i = 0; i < m_noOfEnemies; i++)
	{
		m_enemyArray[ i ].setSpeed( m_initialSpeed);

	}
}

//locates right-most, left-most and bottom-most enemies
void EnemyManager::findBufferEnemies( )
{
	//this func. gets called after an enemy dies - only at this point can there be a new left-most, right-most or bottom-most enemy (prevents this being run every update)
	
	//sets values to opposite of what they would usually be (e.g. leftMost is meant to be the smallest x value, so setting it to something large will kick-start the process)
	float leftMost = 700;
	float rightMost = 0;
	float bottomMost = 0;

	//sets index values of each to 0 
	leftMostI = 0;
	rightMostI = 0;
	bottomMostI = 0;

	//cycles each enemy 
	for (int i = 0; i < m_noOfEnemies; i++)
	{
		//checks if enemy is alive and "more left" than the current leftMost value
		if (m_enemyArray[ i ].getPosition( ).x < leftMost && m_enemyArray[ i ].returnState() == Enemy::EnemyStates::alive)
		{
			//if passed, the left most index is updated to the current val of [i], and leftMost position updated to this enemies position
			leftMostI = i;
			leftMost = m_enemyArray[ i ].getPosition( ).x;
		}

		//checks if enemy is alive and "more right" than the current rightMost value
		//USED TO BE ELSE IF - CAUSED FINAL ENEMY TO ZIP OFF RIGHT SIDE OF SCREEN
		if (m_enemyArray[ i ].getPosition( ).x > rightMost && m_enemyArray[ i ].returnState( ) == Enemy::EnemyStates::alive)
		{
			//if passed, the right most index is updated to the current val of [i], and rightMost position updated to this enemies position
			rightMostI = i;
			rightMost = m_enemyArray[ i ].getPosition( ).x;
		}

		//checks if enemy is alive and "more down" than the current bottomMost value
		if (m_enemyArray[ i ].getPosition( ).y > bottomMost && m_enemyArray[ i ].returnState( ) == Enemy::EnemyStates::alive)
		{
			//if passed, the bottom most index is updated to the current val of [i], and bottomMost position updated to this enemies position
			bottomMostI = i;
			bottomMost = m_enemyArray[ i ].getPosition( ).y;
		}
	}
}