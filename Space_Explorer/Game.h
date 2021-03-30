#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "Projectile.h"
#include "Player.h"
#include "ProjectileManager.h"
#include "ScoreManager.h"
#include "UIManager.h"
#include "ShieldManager.h"

//main game processes, one instance (created & kick-started in Main.cpp)
class Game
{
private:

	//stores dimensions of screen (set to 800 x 900 in Game())
	sf::Vector2f m_playDimensions;
	//instance of Player
	Player m_player = Player( EntityData::entityTextures::ship );
	//instance of EnemyManager
	EnemyManager m_enemyManager;
	//instance of ProjectileManager
	ProjectileManager m_projectileManager;
	//instance of ScoreManager
	ScoreManager m_scoreManager;
	//instance of RenderWindow (window used to display / draw game)
	sf::RenderWindow m_window;
	//instance of ShieldManager
	ShieldManager m_shieldManager;
	//instance of UIManager
	UIManager m_UIManager;

	//SoundClip instance storing menu music
	SoundClip mainMenuMusic = SoundClip("mainMenuMusic.wav");
	//SoundClip instance storing play-time music
	SoundClip gameMusic = SoundClip("gameMusic.wav");

	SoundClip playerDead = SoundClip( "PlayerDead.wav" );
	SoundClip playerLived = SoundClip( "PlayerLived.wav" );

	//instance of Clock (used to get deltaTime)
	sf::Clock m_deltaClock;
	//instance of Time (stores time elapsed since play)
	sf::Time m_timeElapsed;
	//stores last updated value of delta time
	float m_time;
	//changable values passed to player & UIManager
	int m_playerMaxHealth;
	//max health of player (default is 1) and max lives of player (default is 3)
	int m_playerMaxLives;
	//bool val of whether "FIRE" key has been released (e.g. set to TRUE when space is pressed down, doesn't switch to FALSE until space is released - prevents multiple bullets being fired per press of FIRE key
	bool fired = false;

	//stores whether menu has been loaded - set to True once initialisation methods have run, set to False again once currentState is no longer mainMenu
	bool m_menuLoaded = false;
	//stores whether game has been loaded - set to True once initialisation methods have run, set to False again once currentState is no longer playing
	bool m_gameLoaded = false;

	//PRIVATE FUNCTIONS
	
	//runs function needed to display all elements on screen (e.g. player.draw(), UIManager.draw() etc.)
	void drawScreen( );
	//runs function needed to update all elements on screen (e.g. player.Update(), UIManager.UPdate() etc.)
	void updateScreen( );
	//function run each update - checks if m_window is still open. If it is, run the rest of the processes. If not, quit program
	void checkWindowOpen( );
	//detects keyboard input for player firing
	void takeInput( );
	//runs setup methods (initialises all necessary objects & processes)
	void setup( );

public:
	//default constructor
	Game( );
	//destructor
	~Game( );


	//public var. - stores the state the game is currently in (e.g. main menu, playing, game over etc.)
	EntityData::gameState currentState = EntityData::gameState::mainMenu;

	//main run function, bootstrap function called by Main.cpp
	void run( );
};

#endif //GAME_H