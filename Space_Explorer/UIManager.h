#ifndef UIMANAGER_H
#define UIMANAGER_H

#include "TextObject.h"
#include "Player.h"
#include "ScoreManager.h"
#include "EntityData.h"
#include "Button.h"

#include <vector>

//manages all UI displayed to the screen, including buttons, score displays etc.
class UIManager
{
private:
	//stores val of last call of sf::Mouse::isButtonDown() - used to ensure user must press down AND UP AGAIN before being able to select another button
	bool m_prevMouseDown;

	//achievable states of the main menu - main options (play, difficulty etc. ) screen, credits screen or high score screen
	enum class menuState
	{
		mainOptions,
		credits,
		highScores
	};

	//stores current state of screen
	menuState state = menuState::mainOptions;

	//vector (dynamic list) of sprite pointers used to store / display player lives
	std::vector< sf::Sprite *> m_playerHealthDisplay;

	//heart texture - life remaining
	sf::Texture m_heart;
	//heart texture - life lost
	sf::Texture m_lostHeart;

	//scene background (space animation)
	sf::Sprite m_spaceBackground;
	sf::Texture m_spaceBGTexture;
	float m_scrollDistance = 0;

	//main menu buttons
	Button playButton = Button("PLAY");
	Button easyButton = Button("EASY");
	Button normalButton = Button( "NORMAL" );
	Button hardButton = Button( "HARD" );

	Button creditMenuButton = Button( "CREDITS" );
	Button exitButton = Button( "EXIT" );

	//credits buttons
	Button backToMainMenuButton = Button( "MENU" );

	//game over buttons
	Button retry = Button( "RETRY" );
	Button nextLevel = Button( "CONTINUE" );

	//main title ("space explorers") sprite obj. and associated texture
	sf::Texture m_mainMenuTitleText;
	sf::Sprite m_mainMenuText;

	//stores previous number of lives (compares current input to prevLives to see if UI needs updating)
	int prevLives;
	//stores max number of lives player can have at once
	int maxLives;

	//game over (enemies reached bottom or player died) menu pop-up (sprite and texture)
	sf::Sprite gameOverMenuBackground;
	sf::Texture gameOverBackgroundTexture;

	//level complete (all enemies dead) menu pop-up (sprite and texture)
	sf::Sprite levelCompleteMenuBackground;
	sf::Texture levelCompleteTexture;

	//border around play zone (sprite and texture)
	sf::Sprite UILine;
	sf::Texture outlineTexture;

	//pointer to ScoreManager, used to update score / high score UI elements
	ScoreManager * m_scoreManager;

	//text elements needed for UI (score displays, credit text etc.)
	TextObject m_scoreText;
	TextObject m_highScoreText;
	TextObject m_mainMenuInstructions;
	TextObject m_credits;
	TextObject m_newHighScore;
	TextObject m_highScore;

	//data needed to animate title (sine wave bob)
	float m_menuTitleTime;
	sf::Vector2f m_menuTitleInitialPos;
	

public:
	//default constructor
	UIManager( );
	//deconstructor
	~UIManager( );

	//sets up UIManager, creates pointers to score manager & stores screen dimensions
	void initialise( int noOfLives, const sf::Vector2f & screenDimensions, ScoreManager * scoreManager );
	//draws the space background to the screen
	void drawBackground( sf::RenderWindow & window );
	//updates space background (animates)
	void updateBackground( float deltaTime );
	//called after game is reset - re-initialises life counter using playerLives passed as param
	void resetUI( int playerLives );
	//updates UI during play time - uses playerLives to check if life display needs updating
	void updateUIManager( int playerLives );
	//draws UI elements to the screen
	void drawUI( sf::RenderWindow & window );
	//draws main menu UI elements to screen 
	void drawMainMenu( sf::RenderWindow & window );
	//draws game over / level complete elements to screen
	void drawGameOverMenu( EntityData::gameState GameState, sf::RenderWindow & window );

	//returns game state to switch to, updates buttons and checks if player presses one
	EntityData::gameState updateMainMenu( float deltaTime, sf::RenderWindow & window );
	EntityData::gameState updateGameOverMenu( EntityData::gameState state, sf::RenderWindow & window );
};

#endif // UIMANAGER_H