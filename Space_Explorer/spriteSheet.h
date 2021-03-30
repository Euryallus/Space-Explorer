#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>

//intended to be used to store data about spriteSheet imported and used by all Entities, but was twilighted after implementation took too much time
namespace sprite
{
	//neum to store location of sprite specified on grid (4 x 4 grid, each enum val. is a different cell)
	enum class sprites
	{
		enemy1_0 = 0,
		enemy1_1 = 4,
		enemy2_0 = 1,
		enemy2_1 = 5,
		enemy3_0 = 2,
		enemy3_1 = 6,
		projectile_0 = 12,
		projectile_1 = 13,
		heart_0 = 3,
		heart_1 = 7,
		shield_0 = 8,
		shield_1 = 9,
		shield_2 = 10,
		shield_3 = 11
	};

	//moved on to mapping a sprite enum val. to cell int
	std::map <sprites, int> m_spriteMap;

	//stores size of spriteSheet
	const int gridSizeX = 4;
	const int gridSizeY = 4;

	//saves sprite size
	const float spriteSize = 25.f;
	sf::IntRect position( 0, 0, spriteSize, spriteSize );


	void setTexture(sprite::sprites sprite, sf::Sprite & spriteToChange)
	{
		int location = static_cast< int >( sprite );

		position.top = gridSizeY / location;
		position.left = gridSizeX % gridSizeX;

		spriteToChange.setTextureRect( position );
	}

	sf::IntRect setTexture( sprite::sprites sprite )
	{
		int location = static_cast< int >( sprite );

		position.top = location / gridSizeY ;
		position.left = location % gridSizeX;

		return position;
	}
}




#endif //SPRITESHEET_H
