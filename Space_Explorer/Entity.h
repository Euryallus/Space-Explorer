#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "EntityData.h"


//main object class for game (inherrited by Enemy, Player, Projectile etc.)
class Entity : public sf::Sprite
{
protected:

	//default speed of object
	float m_speed;
	//delta time value from the last update
	float m_deltaTime;
	//time between each animation frame (e.g. 0.25f indicates 0.25 seconds between frames)
	float m_animRate = 0.5f;
	//running total of time since last animation frame
	float m_animFrame = 0;

	//health count (amount of health per life, defaults to 1)
	int m_health;
	//maximum pos. value for health (defaults to val. of m_health)
	int m_maxHealth;
	//stores val. for no of frames in the animation (defaults to 1)
	int m_noOfFrames;
	//stores val of current frame shown (defaults to 0, a.k.a the start of the sequence)
	int m_currentFrame = 0;

	//bool indicates whether entity is "active", e.g. whether it should be drawn, should move etc.
	bool m_isActive;

	//stores texture of entity, usually contains 1 or 2 frames of an animation
	sf::Texture m_texture;
	//texture switched to when destroyed (e.g. explosion) - currently only used for enemies
	sf::Texture m_destroyedTexture;

	//stores diretion entity is travelling in (e.g (0, -1) would be travelling up)
	sf::Vector2f m_direction;
	//stores ref. to size of sprite associated with Entity (used for animations)
	sf::Vector2i m_spriteSize;

public:

	//default contructor
	Entity( );
	//constructor w/ input for texture (from enum) and number of anim frames
	Entity(EntityData::entityTextures texture, int noOfFrames ); 
	//default constructor w/ input for no. of anim frames
	Entity( int noOfFrames ); 
	//copy constructor
	Entity(const Entity &) = default; 
	//destructor
	~Entity(); 

	//VIRTUAL FUNCTIONS

	//virtual initialisation func. (sets entity values back to default, puts entity as pos. passed as param)
	virtual void initialise(const sf::Vector2f &position);
	//virtual update func. (by default it only runs .move() and .animate())
	virtual void update(float deltaTime);
	//virtual move func. (by default just takes direction and adjusts position based on speed, direction and delta time)
	virtual void move();
	//vitual damage func. (by default, just removes [damage] from m_health & if m_health = 0, m_active is set to false)
	virtual void takeDamage(int damage);

	//NORMAL FUNCTIONS

	//takes deltaTime as input, incriments m_animFrame by deltaTime value, and if it's over m_animRate moves to the next frame
	void animate( float deltaTime );

	//SETTERS AND GETTERS

	//sets stored direction for entity by taking enum value as input (e.g. if EntityData::entityDirections::Left is input, m_direction = sf::Vector2f(-1, 0))
	void setDirection(EntityData::entityDirections direction);
	//sets m_active bool to value passed (used to "turn off" or "turn on" entities)
	void setActive(bool active);
	//takes possible entity texture from enum parameter, loads file associated w/ enum value and assigns it to Entity (.setTexture())
	void changeTexture(EntityData::entityTextures texture);
	//sets m_speed value
	void setSpeed( float speed );
	//sets time between animation frames (changes m_animRate value)
	void setAnimRate( float rate );

	//returns m_speed value
	float returnSpeed( );
	//returns m_active status
	bool getActive();
	//returns current entity direction
	sf::Vector2f getDirection();
};

#endif //ENTITY_H
