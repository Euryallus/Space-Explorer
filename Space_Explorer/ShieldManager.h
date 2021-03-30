#ifndef SHIELDMANAGER_H
#define SHIELDMANAGER_H

#include "Projectile.h"
#include "Shield.h"

#include "ProjectileManager.h"

//manages shield objects in scene, handles position & collisions
class ShieldManager
{
private:
	//array of shield pieces (max. 50)
	Shield m_shieldArray[ 50 ];

	//defines dimensions of each shield (defaults to 3 x 2) 
	int m_xPerShield = 3;
	int m_yPerShield = 2;
	//defines number of shields total (used to calc. number of pieces required, m_numberOfShields * m_yPerShield * m_xPerShield)
	int m_numberOfShields = 4;

	//stores screen dimensions (used to initialise shields within playspace)
	sf::Vector2f m_screenDimensions;
	float m_spaceBetweenShields = 150;

public:
	//default constructor
	ShieldManager( );
	//destructor
	~ShieldManager( );

	//set-up process for shields, run when game is started / restarted (takes screen dimensions as input to calc. shield positions)
	void initialise( const sf::Vector2f & screenDimensions );
	//uses ProjectileManager to check collisions with active shields - if true damages shield & de-activates projectile
	void checkCollisions( ProjectileManager & pjManager );
	//cycles each active shield and draws to window
	void draw( sf::RenderWindow & window );
};

#endif //SHIELDMANAGER_H