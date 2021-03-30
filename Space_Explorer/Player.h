#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "Entity.h"
#include "Projectile.h"

//Player class, inherits from Entity
class Player :
    public Entity
{
private:
    
    //stores value for max health the player can have
    int m_maxHealth;
    //stores value for max lives the player can have
    int m_maxLives;
    //current no. of lives (<= m_maxLives)
    int m_lives;
    //bool flagging if the player has been hit within the last second (used when displaying red flash when player is hit)
    bool m_hasBeenHit = false;
    //float counter used when player flashes red after hit
    float m_damageColourEffect = 0;
    //stores screen size
    sf::Vector2f m_screenDimensions;

    

public:
    //constructor (takes texture parameter)
    Player(EntityData::entityTextures texture);
    //default constructor
    Player();
    //destructor
    ~Player();

    //sets up object (resets values to default, places player at co-ords passed w/ [x] health and lives
    void initialise(const sf::Vector2f & maxPos,  int maxLives, int maxHealth);

    //Entity override of Update function
    void update(float deltaTime); 
    //Entity override of takeDamage function (allows additional effects like red flash to be triggered when hit)
    void takeDamage(int damage);
    //takes an Entity object and returns true if object passed is overlapping / intersecting self
    bool checkCollision(Entity object);
    
    //GETTERS & SETTERS

    //returns current number of lives
    int returnLives();
    //returns max lives player can get (e.g. in easy mode, this would return 4) - defined in initialisation (passed from Game instance)
    int returnMaxLives();

};

#endif //PLAYER_H
