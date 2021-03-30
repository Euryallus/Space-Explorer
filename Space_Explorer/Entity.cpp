#include "Entity.h"
#include <SFML/Graphics.hpp>

//main base class for all "active" game elements (e.g. enemies, player, projectiles etc)
Entity::Entity( )
{
}

//constructor with pre-determined texture
Entity::Entity(EntityData::entityTextures texture, int noOfFrames ) 
{
	//sets number of anim frames to number passed, assigns texture specified, loads destroyedTexture and defaults active to false
	m_noOfFrames = noOfFrames;
	changeTexture(texture);

	m_destroyedTexture.loadFromFile("dead.png");
	m_isActive = false; 
}

//constructor for Entity that has texture assigned at some other point
Entity::Entity( int noOfFrames )
{
	m_noOfFrames = noOfFrames;
	m_isActive = false;
}

//destructor
Entity::~Entity()
{
}

//virtual initialise func.
void Entity::initialise(const sf::Vector2f &position) 
{
	//sets active to true, initialises object to position defined & sets origin to middle of sprite
	setPosition(position);
	setOrigin(getLocalBounds().width / 2, getLocalBounds().height / 2);

	//default animation rate is 0.5, can be changed
	m_animRate = 0.5f;

	//when intitialised, entity is "activated" 
	m_isActive = true;
	//sets direction to 0,0 (unmoving)
	m_direction = sf::Vector2f(0.f, -0.f); 
	m_currentFrame = 0;
}

//virtual update for entities
void Entity::update(float deltaTime)
{
	//if the Entity is flagged as an animated sprite (e.g. frames > 1) animate it
	if (m_noOfFrames > 1)
	{
		animate( deltaTime );
	}

	//stores latest deltaTime value for use in move()
	m_deltaTime = deltaTime;
	move();
}

//sets Entity direction as left, right, up, down or stationary using EntityData enum val
void Entity::setDirection(EntityData::entityDirections direction)
{
	switch (direction) //sets direction of object based on param enum input
	{
	case EntityData::entityDirections::left:
		m_direction = sf::Vector2f(-1.f, 0.f);
		break;

	case EntityData::entityDirections::right:
		m_direction = sf::Vector2f(1.f, 0.f);
		break;

	case EntityData::entityDirections::up:
		m_direction = sf::Vector2f(0.f, -1.f);
		break;

	case EntityData::entityDirections::down:
		m_direction = sf::Vector2f(0.f, 1.f);
		break;

		//downLarge and upLarge are used by enemies when turning around (e.g. drop a row & turn around)
	case EntityData::entityDirections::downLarge:
		m_direction = sf::Vector2f(0.f, 75.f);
		break;

	case EntityData::entityDirections::upLarge:
		m_direction = sf::Vector2f(0.f, -75.f);
		break;


	case EntityData::entityDirections::stationary:
		m_direction = sf::Vector2f(0.f, 0.f);
		break;

	default:
		break;
	}
}

sf::Vector2f Entity::getDirection()
{
	//returns vector2 direction
	return m_direction; 
}

//moves entity in direction stored by speed (time compensated)
void Entity::move() 
{
	setPosition(getPosition() + (getDirection() * m_deltaTime * m_speed));
}

void Entity::takeDamage(int damage) 
{
	//decrements health by amount specified
	m_health -= damage;

	//if health == 0, active 0 false
	if (m_health == 0) 
	{
		m_isActive = false;
	}
}

void Entity::setActive(bool active)
{
	//sets active
	m_isActive = active; 
}

bool Entity::getActive()
{
	//returns active
	return m_isActive; 
}

void Entity::changeTexture(EntityData::entityTextures texture)
{
	//loads texture depending on parameter
	switch (texture)  
	{
	case EntityData::entityTextures::ship:
		if (!m_texture.loadFromFile("shipImage.png"))
		{
		}
		break;
	
	case EntityData::entityTextures::enemy1:
		if (!m_texture.loadFromFile("enemy1_s.png"))
		{
		}
		break;
	
	case EntityData::entityTextures::enemy2:
		if (!m_texture.loadFromFile("enemy2_s.png"))
		{
		}
		break;
	
	case EntityData::entityTextures::enemy3:
		if (!m_texture.loadFromFile("enemy3_s.png"))
		{
		}
		break;
	
	case EntityData::entityTextures::projectile:
		if (!m_texture.loadFromFile("projectile_s.png"))
		{
		}
		break;

	case EntityData::entityTextures::spaceBackground:
		if(!m_texture.loadFromFile("background.png" ))
		{
		}
	
	default:
		break;
	}
	//sets texture, assignes sprite size, sets texture rect to frame 1 of anim
	setTexture(m_texture, false);
	m_spriteSize = sf::Vector2i( m_texture.getSize().x, m_texture.getSize( ).y / (m_noOfFrames));
	
	setTextureRect(sf::IntRect( 0, 0, m_spriteSize.x, m_spriteSize.y ));
}

void Entity::setSpeed( float speed )
{
	//sets speed of Entity
	m_speed = speed;
}

float Entity::returnSpeed( )
{
	//returns speed of Entity
	return m_speed;
}

void Entity::animate( float deltaTime )
{
	//increments time since last frame using deltaTime
	m_animFrame += deltaTime;

	if (m_animFrame > m_animRate) //if the time since last frame > frame rate specified, go to next frame
	{
		++m_currentFrame;
		m_animFrame = 0.f;

		if (m_currentFrame == m_noOfFrames) //if reached last frame, reset to 0
		{
			m_currentFrame = 0;
		}

		//sets texture to show current frame
		setTextureRect( sf::IntRect( 0, m_currentFrame * m_spriteSize.y, m_spriteSize.x, m_spriteSize.y) );
	}

}

void Entity::setAnimRate( float rate )
{
	//sets rate frames change in animation
	m_animRate = rate;
}


