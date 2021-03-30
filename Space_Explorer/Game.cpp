#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

#include "DifficultyData.h"
#include "Game.h"

//main game class
Game::Game( )
{
	//sets difficulty values, defaults player health & lives
	difficulty::setupDifficultyData( );

	m_playerMaxHealth = 1;
	m_playerMaxLives = 3;

	//stores size of window & creates window
	m_playDimensions = sf::Vector2f( 800.f, 900.f );
	m_window.create( sf::VideoMode( m_playDimensions.x, m_playDimensions.y ), "Space Explorer" );

	//runs set-up functions for managers and initialises player
	m_enemyManager.setUp( m_playDimensions, &m_scoreManager );
	m_projectileManager.assignEnemyManager( &m_enemyManager );
	m_UIManager.initialise( m_playerMaxLives, m_playDimensions, &m_scoreManager );
	m_shieldManager.initialise( m_playDimensions );

	m_player.initialise( m_playDimensions, m_playerMaxLives, m_playerMaxHealth );
}

//destructor
Game::~Game( )
{
}

//run when game starts
void Game::setup( )
{
	//re-initialises all managers, elements etc. to default position / values

	m_playerMaxLives = difficulty::playerLives[ static_cast< int >( difficulty::currentDifficultyEnum ) ];
	m_enemyManager.setUp( m_playDimensions, &m_scoreManager );
	m_player.initialise( m_playDimensions, m_playerMaxLives, m_playerMaxHealth );

	m_UIManager.resetUI( m_playerMaxLives );
	m_projectileManager.reset( );

	m_shieldManager.initialise( m_playDimensions );	

	//resets random "seed" so enemy bullet spawns are truly "random"
	srand( static_cast< int >( time( NULL ) ) );
}

void Game::run( )
{
	while (m_window.isOpen( )) 
	{
		//while the render window is open, grab time since last update (delta time)
		m_timeElapsed = m_deltaClock.restart( );
		m_time = m_timeElapsed.asSeconds( );

		checkWindowOpen( );

		//updates elements then draws to screen
		updateScreen( );

		drawScreen( );
	}

}

//run to draw game to RenderWindow
void Game::drawScreen( )
{
	//clears previous renders & draws space background underneath all other elements
	m_window.clear( );
	m_UIManager.drawBackground( m_window );

	//runs a different set of methods based on currentState
	switch (currentState)
	{
	case EntityData::gameState::playing:
		//renders player if it's flagged as active
		if (m_player.getActive( ))
		{
			m_window.draw( m_player );
		}

		//cycles each manager and runs draw functions (passes RenderWindow as param to allow window.draw() to be accessed inside 'em)
		m_enemyManager.draw( m_window );
		m_projectileManager.drawProjectiles( m_window );

		m_shieldManager.draw( m_window );
		m_UIManager.drawUI( m_window );

		break;


	case EntityData::gameState::levelFailed:
	case EntityData::gameState::playerDead:
	case EntityData::gameState::levelComplete:
		//same function run for levelFailed, playerDead & levelComplete - differentiation between display happens inside drawGameOverMenu()
		m_UIManager.drawGameOverMenu( currentState, m_window );
		break;

	case EntityData::gameState::mainMenu:		
		m_UIManager.drawMainMenu( m_window );
		break;

	default:
		break;
	}

	//calls final render function needed to display game to window
	m_window.display( );
}

void Game::updateScreen( )
{
	m_UIManager.updateBackground( m_time );
	//runs a different set of methods based on currentState
	switch (currentState)
	{
	case EntityData::gameState::playing:
		//ensures initial functions needed for main menu are run next time state switches to mainMenu
		m_menuLoaded = false;

		//if the game hasn't yet been loaded, run load functions & start playing music
		if (m_gameLoaded == false)
		{
			setup( );
			m_projectileManager.spawnEnemyProjectile( m_enemyManager.enemyShoot( ) );
			gameMusic.play( );
			mainMenuMusic.stop( );
			m_gameLoaded = true;
		}

		//updates each component
		takeInput( );

		m_player.update( m_time );
		m_enemyManager.update( m_time );

		m_projectileManager.updateProjectiles( m_player,  m_time );
		m_shieldManager.checkCollisions( m_projectileManager );

		m_UIManager.updateUIManager( m_player.returnLives( ) );

		//checks if EnemyManager bool after update's run - flags level complete if oneIsStillActive = false
		if (!m_enemyManager.oneIsStillActive)
		{
			playerLived.play( );
			currentState = EntityData::gameState::levelComplete;
		}

		//checks if EnemyManager bool after update's run - flags game over if enemy has reached bottom of screen
		if (m_enemyManager.hasHitBottom)
		{
			playerDead.play( );
			currentState = EntityData::gameState::levelFailed;
		}

		//checks if player's run out of lives - flags game over
		if (m_player.returnLives( ) == 0)
		{
			playerDead.play( );
			currentState = EntityData::gameState::playerDead;
		}

		break;

	case EntityData::gameState::gameOver:
	case EntityData::gameState::levelComplete:
	case EntityData::gameState::playerDead:
		//sets loaded status to false
		m_menuLoaded = false;
		m_gameLoaded = false;

		//sets currentState to state passed from UIManager update (will return mainMenu or playing if menu button or retry button is pressed)
		currentState = m_UIManager.updateGameOverMenu( currentState, m_window );
		break;

	case EntityData::gameState::mainMenu:

		//sets game loaded status to false
		m_gameLoaded = false;

		//runs initial functions if menu is not yet loaded
		if (m_menuLoaded == false)
		{
			mainMenuMusic.play( );
			gameMusic.stop( );
			m_menuLoaded = true;
		}
		
		//updates current state based on UIManager update (returns playing or mainMenu based on if "play" was pressed
		currentState = m_UIManager.updateMainMenu( m_time, m_window );

		break;

	default:
		break;
	}
}

void Game::checkWindowOpen( )
{
	//checks if window was closed during last update
	sf::Event event;
	while (m_window.pollEvent( event ))
	{
		if (event.type == sf::Event::Closed)
			m_window.close( );
	}
}

void Game::takeInput( )
{
	//takes input for player bullet fire
	if (sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) && fired == false)
	{
		//if space was pressed & space was just pressed, fire a projectile
		m_projectileManager.spawnPlayerProjectile( m_player.getPosition( ) );
		fired = true;
	}

	if (!sf::Keyboard::isKeyPressed( sf::Keyboard::Space ))
	{
		//only allow another bullet to be fired once space has been released again
		fired = false;
	}
}