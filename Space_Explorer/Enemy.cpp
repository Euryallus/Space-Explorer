#include "Enemy.h"
#include "Entity.h"

//Enemy class, inherrited from Entity
Enemy::Enemy( EntityData::entityTextures texture )
	: Entity( texture, 2) //passes texture param to Entity constructor, and defaults no. of animation frames to 2
{
	//assigns speed, default state, origin, health etc.
	m_speed = 25.f;
	currentState = Enemy::EnemyStates::alive;
	setOrigin( getLocalBounds( ).width / 2, getLocalBounds( ).height / 2 );
	m_deathTime = 0.25f;
	m_deathTimeElapsed = 0;
	m_health = 1;
}

//default constructor
Enemy::Enemy( )
	: Entity( EntityData::entityTextures::enemy1, 2 )
{
	//assigns speed, default state, origin, health etc.
	m_speed = 25.f;
	currentState = Enemy::EnemyStates::alive;
	setOrigin( getLocalBounds( ).width / 2, getLocalBounds( ).height / 2 );
	m_deathTime = 0.25f;
	m_deathTimeElapsed = 0;
	m_health = 1;
}

//destructor
Enemy::~Enemy( )
{
}

//overridden from Entity
void Enemy::initialise( const sf::Vector2f & position )
{
	//sets state to alive & active (currentState is local to Enemy, m_isActive is used by Entity - an Enemy is still "Active" if it's been destroyed but still rendered as an explosion)
	currentState = Enemy::EnemyStates::alive; 
	m_isActive = true;

	//sets animation elements to default (sets texture rect to top frame, assigns texture, sets time running to 0 (m_animFrame)
	setTextureRect( sf::IntRect( 0, 0, m_spriteSize.x, m_spriteSize.y ) );
	setTexture( m_texture );
	m_animFrame = 0.f;

	//sets vars needed for "death" - m_deathTime is amount of time explosion shows for after death, m_deathTimeElapsed is running total of time since death
	m_deathTime = 0.5f;
	m_deathTimeElapsed = 0;
	m_health = 1;

	//runs base initialise func. from Entity
	Entity::initialise( position );
}

//overridden from Entity
void Enemy::update( float deltaTime )
{
	m_deltaTime = deltaTime; //assigns delta time

	//if enemy is still alive, run base update func (moves Entity in direction stored by speed * delta time & animates Entity)
	if (currentState == Enemy::EnemyStates::alive)
	{
		Entity::update( deltaTime );
	}

	//if enemy is to be rendered but is not "alive", increment death timer, animate, and if timer = m_deathTime set state to dead
	if (currentState == Enemy::EnemyStates::destroyed)
	{
		m_deathTimeElapsed += deltaTime;

		animate( deltaTime );

		if (m_deathTimeElapsed >= m_deathTime)
		{
			currentState = Enemy::EnemyStates::dead;
		}
	}
}

void Enemy::die( )
{
	//assigns explosion texture to Enemy
	setTexture( m_destroyedTexture );
	//resets animation 
	m_animFrame = 0;
	//sets state to "destroyed" & plays noise to reflect hit
	currentState = Enemy::EnemyStates::destroyed;

	noise.play( );
}

Enemy::EnemyStates Enemy::returnState( )
{
	//returns enemy's state (used to check collisions)
	return currentState;
}

//overridden func. from Entity, allows die() to be called
void Enemy::takeDamage( int damage )
{
	//decrements m_health
	m_health -= damage;
	//if no health remains, run die()
	if (m_health == 0)
	{
		die( );
	}
}