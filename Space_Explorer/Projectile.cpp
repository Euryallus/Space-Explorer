#include "Projectile.h"
#include "Entity.h"

//projectile class, inherits from Entity
Projectile::Projectile()
	: Entity(EntityData::entityTextures::projectile, 2)
{
	//calls Entity constructor w/ projectile texture & 2 animation frames flagged
}

//destructor
Projectile::~Projectile()
{
}



