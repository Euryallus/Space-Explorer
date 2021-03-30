#ifndef PROJECTILEMANAGER_H
#define PROJECTILEMANAGER_H

#include "Projectile.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "Player.h"
#include "Entity.h"
#include "Shield.h"

#include "SFML/Graphics/Rect.hpp"

//Keeps track of projectiles fired & their collisions with other game elements (e.g. enemies, players etc.)
class ProjectileManager
{
private:
	//array of player projectiles
	Projectile m_player1Projectiles[ 20 ];
	//array of enemy projectiles
	Projectile m_enemyProjeciles[ 20 ]; 

	//pointers to last activated proj. in array (for player & enemy)
	int m_player1Pointer;
	int m_enemyPointer;

	//pointer to enemy manager (used to check collisions)
	EnemyManager * m_enemyManager;

	//stores default speed of enemy projectiles (is changed with difficulty)
	float m_enemyProjectileSpeed = 400.f;
	//stores defalt number of projectiles a player can have active at once (is changed with difficulty)
	int m_maxPlayerShots = 1;
	//stores default speed increase for enemies (when one is destroyed, rest increase speed - is changed w/ difficulty)
	float m_enemySpeedIncrease = 2.f;

	//sound effect played when enemy or player shoots bullet
	SoundClip shootSFX = SoundClip( "Shoot.wav" ); //sound clip

	SoundClip m_playerHurt = SoundClip( "PlayerHurt.wav" );

public:
	//default constructor
	ProjectileManager( );
	//destructor
	~ProjectileManager( );

	//stores enemyManager pointer as * m_enemyManager to be used in collision detection later
	void assignEnemyManager( EnemyManager * enemyManager );
	//initialises new player projectile at point specified IF total number allowed active has not been reached
	void spawnPlayerProjectile( const sf::Vector2f & position );
	//initialises new enemy projectile at point specified (randomly generated co-ord of enemy, found by EnemyManager)
	void spawnEnemyProjectile( const sf::Vector2f & position );

	//cycles each active projectile and updates it (takes player ref. to use in checkPlayerCollisions)
	void updateProjectiles( Player & player, float deltaTime );
	//uses EnemyManager to check each active projectile against an enemy - if EnemyManager.checkEnemyProjectileCollisions() returns true, projectile it collided w/ is de-activated
	void checkEnemyCollisions( );
	//checks collisions with shield pieces, disables projectile if it's collided
	bool checkShieldCollisions( Shield & shield );
	//checks collisions with player, disables projectile if it's collided
	void checkPlayerCollisions( Player & player );
	//draw each active projectile to the screen
	void drawProjectiles( sf::RenderWindow & window );

	//resets all projectiles to default position & active status
	void reset( );
};

#endif //PROJECTILEMANAGER_H