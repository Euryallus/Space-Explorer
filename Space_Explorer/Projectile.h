#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Entity.h"

//Projectile class, inherits from Entity
class Projectile :
    public Entity
{
private:

public: 
    //default constructor
    Projectile();
    //destructor
    ~Projectile();
};

#endif //PROJECTILE_H