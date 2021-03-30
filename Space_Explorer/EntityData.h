#ifndef ENTITYDATA_H
#define ENTITYDATA_H

//namespace storing enum values for entity textures, directions and game states
namespace EntityData 
{
	//possible textures used by Entity class (used in Entity.changeTexture())
	enum class entityTextures
	{
		ship,
		enemy1,
		enemy2,
		enemy3,
		projectile,
		spaceBackground
	};

	//possible default directions used by Entity class (used in Entity.changeDirection(), Entity.move() etc.)
	enum class entityDirections
	{
		left,
		right,
		up,
		down,
		downLarge,
		upLarge,
		stationary
	};

	//possible game states (each has different update processes associated with it, stored as currentState in Game)
	enum class gameState
	{
		mainMenu,
		playing,
		gameOver,
		playerDead,
		levelFailed,
		levelComplete
	};
}

#endif