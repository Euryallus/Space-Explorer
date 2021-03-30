#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include "Enemy.h"
#include "Projectile.h"

#include "ScoreManager.h"

//Enemy controller class, handles "unit" behaviour of enemies
class EnemyManager
{
private:

	//default enemy array - max 100. active enemies at once
	Enemy m_enemyArray[ 100 ];

	//no. of enemies in level, number of enemies per row / column
	int m_noOfEnemies = 55; 
	int m_noOfRows = 5;
	int m_noOfColumns = 11;

	//m_enemyArray index values of left-most, right-most and bottom-most enemies (used to check if enemies each bounds of the screen)
	int leftMostI;
	int rightMostI;
	int bottomMostI;

	//vectors storing screen dimensions and distance desired between enemies
	sf::Vector2f m_distanceBetweenEnemies = sf::Vector2f( 50.0f, 50.0f );
	sf::Vector2f m_screenDimensions;

	//delta time for last update, passed from Game
	float m_deltaTime;

	//pointer to ScoreManager object (used by Game)
	ScoreManager * m_scoreManager;

	//stores enum value defined in Entity::Data namespace (all possible directions of enemies)
	EntityData::entityDirections m_movementDirection;

public:

	//public bool flagging if at least one enemy is still alive
	bool oneIsStillActive;
	//public bool flagging if an enemy has hit the bottom of the "screen" (below the shields)
	bool hasHitBottom;

	//float storing initial speed of enemies (as defined in the Enemy class)
	float m_initialSpeed;

	//default contructor
	EnemyManager( );

	//deconstructor
	~EnemyManager( );

	//update: runs once each frame
	void update( float deltaTime );
	//draw: cycles each enemy and draws it to the screen depending on state (active / inactive)
	void draw( sf::RenderWindow & window );
	//setUp: initialises EnemyManager, resets to default values (used to re-start game during playtime)
	void setUp( const sf::Vector2f & screenDimensions, ScoreManager * scoreManager );
	//move: carries out movement operations (cycles each enemy in m_enemyArray)
	void move( );
	//checkEnemyProjectileCollisions: passed projectiles from ProjectileManager object, returns true if object collides with enemy
	bool checkEnemyProjectileCollisions( const Projectile & proj );
	//increaseSpeed: cycles each enemy and sets speed to newSpeed passed as param
	void increaseSpeed( float newSpeed );
	//findBufferEnemies: locates & alters values of rightMostI, leftMostI and bottomMostI based on locations of enemies - called when checkEnemyProjectileCollisions returns true
	void findBufferEnemies( );

	//enemyShoot: called by Game object, generates enemy bullet at co-ords passed
	sf::Vector2f enemyShoot( );
};

#endif //ENEMYMANAGER_H