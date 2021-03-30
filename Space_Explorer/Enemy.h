#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "SoundClip.h"

//Enemy object class, inherrited from Entity
class Enemy :
	public Entity
{
private:

	//sound clip made with enemy fires bullet
	SoundClip noise;

	//amount of time spent displaying "explosion" texture after being hit
	float m_deathTime = 0.5f;
	//amount of time enemy has spent "dead"
	float m_deathTimeElapsed;

public:

	//"state" of each enemy - Alive = rendered & moving, dead = not moving byt explosion is rendered, destroyed = inactive & un-moving
	enum class EnemyStates
	{
		alive,
		dead,
		destroyed
	};

	//stores current "state" of enemy
	EnemyStates currentState;

	//constructor (takes texture indicator, e.g. ship1)
	Enemy( EntityData::entityTextures texture );
	//default contructor
	Enemy( );
	//destructor
	~Enemy( );

	//initialise: sets all values to defaults, returns ships to "alive / active" states & start position / direction
	void initialise( const sf::Vector2f & position );

	//update: runs each frame, handles enemy collisions movevent etc.
	void update( float deltaTime );

	//die: kick-starts death animation & alters state of enemy to "dead"
	void die( );

	//returnState: returns the currentEnemyState of the enemy (e.g alive, dead or destroyed)
	Enemy::EnemyStates returnState( );

	//takeDamage: polymorphed Entity::takeDamage() (allows die() to be called if m_health == 0)
	void takeDamage( int damage );
};

#endif //ENEMY_H
