
#include "UIManager.h"
#include "TextObject.h"
#include "DifficultyData.h"


#include <math.h>
#include <iostream>

//manages UI elements
UIManager::UIManager( )
{
}

//desctructor
UIManager::~UIManager( )
{
	//deletes each item in life vect. and sets item to nullptr
	for (size_t i = 0; i < m_playerHealthDisplay.size( ); i++) 
	{
		delete m_playerHealthDisplay[ i ];

		m_playerHealthDisplay[ i ] = nullptr;
	}

	m_scoreManager = nullptr;
}

//initialises manager
void UIManager::initialise( int noOfLives, const sf::Vector2f & screenDimensions, ScoreManager * scoreManager )
{
	//stores ref. to ScoreManager
	m_scoreManager = scoreManager;

	//attempts to load heart texture from file
	if (!m_heart.loadFromFile( "heart.png" ))
	{
		//error
	}

	//attempts to load lost heart texture from file
	if (!m_lostHeart.loadFromFile( "lostHeart.png" ))
	{
		//error
	}

	//sets up vector list of heart icons
	if (m_playerHealthDisplay.size( ) == 0) 
	{
		for (int i = 0; i < noOfLives; i++)
		{
			//creates new heart sprite for each life player has
			m_playerHealthDisplay.push_back( new sf::Sprite );
			//assigns texture
			m_playerHealthDisplay[ i ]->setTexture( m_heart ); 
			//moves to position specified
			m_playerHealthDisplay[ i ]->setPosition( sf::Vector2f( screenDimensions.x * 0.1f + ( i * 30 ), 20 ) ); 
		}
	}
	else
	{
		//initialisation not called at start?? error
	}

	//sets prevLives to lives player starts with 
	prevLives = noOfLives;

	//attemts to load UI textures from files
	if(!gameOverBackgroundTexture.loadFromFile( "gameOverOverlay.png" ))
	{
		//error
	}

	if (!levelCompleteTexture.loadFromFile( "levelCompleteOverlay.png" ))
	{
		//error
	}

	if (!outlineTexture.loadFromFile( "outline.png" ))
	{
		//error
	}

	if (m_mainMenuTitleText.loadFromFile( "title.png" ))
	{
		//error	
	}

	if (m_spaceBGTexture.loadFromFile( "background.png" ))
	{
		//error
	}


	//Game Over menu background
	gameOverMenuBackground.setTexture( gameOverBackgroundTexture );
	gameOverMenuBackground.setOrigin( gameOverMenuBackground.getLocalBounds( ).width / 2, gameOverMenuBackground.getLocalBounds( ).height / 2 );
	gameOverMenuBackground.setPosition( screenDimensions.x / 2, screenDimensions.y / 2 );

	//Level Complete menu background
	levelCompleteMenuBackground.setTexture( levelCompleteTexture );
	levelCompleteMenuBackground.setOrigin( gameOverMenuBackground.getLocalBounds( ).width / 2, gameOverMenuBackground.getLocalBounds( ).height / 2 );
	levelCompleteMenuBackground.setPosition( screenDimensions.x / 2, screenDimensions.y / 2 );

	//Play zome outline
	UILine.setTexture( outlineTexture );
	UILine.setScale( sf::Vector2f( 0.9f, 0.9f ) );
	UILine.setOrigin( UILine.getLocalBounds( ).width / 2, UILine.getLocalBounds( ).height / 2 );
	UILine.setPosition( screenDimensions.x / 2, screenDimensions.y / 2 );
	
	//score display
	m_scoreText.setText( "Score: " );
	m_scoreText.setPosition( screenDimensions.x / 2, m_playerHealthDisplay[ 0 ]->getPosition( ).y );
	m_scoreText.setFillColor( sf::Color::White );
	m_scoreText.setCharacterSize( 20 );
	//high score display
	m_highScoreText.setText( "Hi-score: " );
	m_highScoreText.setPosition( screenDimensions.x / 1.25f, m_playerHealthDisplay[ 0 ]->getPosition( ).y );
	m_highScoreText.setFillColor( sf::Color::White );
	m_highScoreText.setCharacterSize( 20 );
	//new high score display
	m_newHighScore.setPosition( screenDimensions.x / 2, (screenDimensions.y / 3 * 2) - 30 );
	m_newHighScore.setFillColor( sf::Color::White );
	m_newHighScore.setCharacterSize( 20 );
	m_newHighScore.setText( "NEW HIGH SCORE" );

	m_highScore.setPosition( screenDimensions.x / 2, screenDimensions.y / 3 * 2 );
	m_highScore.setFillColor( sf::Color::White );
	m_highScore.setCharacterSize( 20 );
	m_highScore.setText( "" );

	//space background
	m_spaceBackground.setTexture( m_spaceBGTexture );
	m_spaceBackground.setTextureRect( sf::IntRect( 0, 0, screenDimensions.x, screenDimensions.y ) );

	//main title
	m_mainMenuText.setTexture( m_mainMenuTitleText );
	m_mainMenuText.setOrigin( m_mainMenuText.getLocalBounds( ).width / 2, m_mainMenuText.getLocalBounds( ).height / 2 );
	m_mainMenuText.setPosition( screenDimensions.x / 2, screenDimensions.y / 6 );

	//play button
	playButton.setPosition( sf::Vector2f(screenDimensions.x / 2, screenDimensions.y / 2 - 100));

	//difficulty buttons
	//easy button
	easyButton.setPosition( sf::Vector2f( (screenDimensions.x / 4), screenDimensions.y / 2 + 25 ) );
	easyButton.setButtonScale( 0.5f );
	//normal button
	normalButton.setPosition( sf::Vector2f( screenDimensions.x / 2, screenDimensions.y / 2 + 25 ) );
	normalButton.setButtonScale( 0.5f );
	//hard button
	hardButton.setPosition( sf::Vector2f( (screenDimensions.x / 4) * 3, screenDimensions.y / 2 + 25 ) );
	hardButton.setButtonScale( 0.5f );

	//credits menu button
	creditMenuButton.setPosition( sf::Vector2f(  screenDimensions.x / 2 , screenDimensions.y / 2 + 200) ) ;
	creditMenuButton.setButtonScale( 0.75f );
	//game exit button
	exitButton.setPosition( sf::Vector2f( screenDimensions.x / 2, screenDimensions.y / 2 + 350 ) );
	exitButton.setButtonScale( 0.75f );
	//return to menu button
	backToMainMenuButton.setPosition( sf::Vector2f( screenDimensions.x / 2, screenDimensions.y / 2 + 250 ) );
	backToMainMenuButton.setButtonScale( 0.75f );
	//restart level button
	retry.setPosition( sf::Vector2f( screenDimensions.x / 2, screenDimensions.y / 2  ) );
	retry.setButtonScale( 0.75f );
	//next level button
	nextLevel.setPosition( sf::Vector2f( screenDimensions.x / 2, screenDimensions.y / 2 ) );
	nextLevel.setButtonScale( 0.75f );
	
	//credits text
	m_credits.setText( "CREDITS\n\n\nHugo Bailey - Developer\n\nTiago Amora - Spaceport 2006 font\n\nBeetlemuse - Menu audio\n\nAndrewkn - Gameplay music\n\nSFXR - sound effect generation" );
	m_credits.setPosition( sf::Vector2f(  screenDimensions.x / 2, screenDimensions.y / 3 ) );
	m_credits.setFillColor( sf::Color::Cyan );

	//stores vars needed to make title bob on sine wave
	m_menuTitleInitialPos = m_mainMenuText.getPosition( );
	m_menuTitleTime = 0;
}

void UIManager::drawBackground( sf::RenderWindow & window )
{
	//animates & draws space background
	window.draw( m_spaceBackground );
}

void UIManager::updateBackground( float deltaTime )
{
	//increases distance scrolled since last "reset" and scales for slower scrolling
	m_scrollDistance += deltaTime * 0.05f;

	//if moved past 2x original height
	if (m_scrollDistance > 2.f)
	{
		//reset distance
		m_scrollDistance -= m_scrollDistance;
	}

	m_spaceBackground.setTextureRect( sf::IntRect( 0, 900 * m_scrollDistance, m_spaceBackground.getLocalBounds( ).width, m_spaceBackground.getLocalBounds( ).height ) );

}

//re-initialises UI on play
void UIManager::resetUI( int playerLives )
{
	//clears m_playerHealthDisplay vector
	m_playerHealthDisplay.clear( );

	//initialises [playerLives] number of hearts to show lives left
	for (int i = 0; i < playerLives; i++)
	{
		//assigns texture
		m_playerHealthDisplay.push_back( new sf::Sprite );
		m_playerHealthDisplay[ i ]->setTexture( m_heart ); 
		//assigns position
		m_playerHealthDisplay[ i ]->setPosition( sf::Vector2f( 50.f + ( i * 30.f ), 20.f ) ); 
	}

	prevLives = playerLives;
}

void UIManager::updateUIManager( int playerLives ) //updates life display
{
	//checks if number of lives has changed - if so, update UI to reflect
	if (playerLives != prevLives)
	{
		m_playerHealthDisplay[ playerLives  ]->setTexture( m_lostHeart );
	}

	//sets notice for number of lives
	prevLives = playerLives;
}

void UIManager::drawUI( sf::RenderWindow & window ) //draws hearts using RenderWindow ref
{
	//draws each heart in array
	for (sf::Sprite * heart : m_playerHealthDisplay)
	{
		window.draw( *heart );
	}

	//updates score & high score text components
	m_scoreText.setText( "Score: " + std::to_string( m_scoreManager->returnCurrentScore( ) ) );
	m_highScoreText.setText( "Hi-score: " + std::to_string( m_scoreManager->returnHighScore( ) ) );

	//displays text
	window.draw( m_scoreText );
	window.draw( m_highScoreText );

	//draws play outline
	window.draw( UILine );
}

//updates main menu
EntityData::gameState UIManager::updateMainMenu( float deltaTime, sf::RenderWindow & window)
{
	//stores mouse position as int vector2
	sf::Vector2i mousePosition = sf::Mouse::getPosition( window );
	//new Y position of menu title
	float newY = m_menuTitleInitialPos.y + ( sin( m_menuTitleTime * 2 ) * 20 );

	//performs different methods based on current state
	switch (state)
	{
	case UIManager::menuState::mainOptions:
		//updates main title text position
		m_mainMenuText.setPosition( sf::Vector2f( m_menuTitleInitialPos.x, newY ) );
		m_menuTitleTime += deltaTime;

		switch (difficulty::currentDifficultyEnum)
		{
		case  difficulty::difficultySetting::Easy:
			playButton.tint( Button::colourTint::Green );
			break;

		case difficulty::difficultySetting::Normal:
			playButton.tint( Button::colourTint::Orange );
			break;

		case difficulty::difficultySetting::Hard:
			playButton.tint( Button::colourTint::Red );
			break;

		default:
			break;
		}

		//checks position of mouse against buttons in main options
		//if mouse intersects and mouse is pressed, change difficulty / start game / exit application
		if (easyButton.checkIntersection( mousePosition ) && sf::Mouse::isButtonPressed( sf::Mouse::Left ) && m_prevMouseDown == false)
		{
			difficulty::currentDifficultyEnum = difficulty::difficultySetting::Easy;
		}

		if (normalButton.checkIntersection( mousePosition ) && sf::Mouse::isButtonPressed( sf::Mouse::Left ) && m_prevMouseDown == false)
		{
			difficulty::currentDifficultyEnum = difficulty::difficultySetting::Normal;
		}

		if (hardButton.checkIntersection( mousePosition ) && sf::Mouse::isButtonPressed( sf::Mouse::Left ) && m_prevMouseDown == false)
		{
			difficulty::currentDifficultyEnum = difficulty::difficultySetting::Hard;
		}

		if (creditMenuButton.checkIntersection( mousePosition ) && sf::Mouse::isButtonPressed( sf::Mouse::Left ) && m_prevMouseDown == false)
		{
			state = menuState::credits;
		}

		if (exitButton.checkIntersection( mousePosition ) && sf::Mouse::isButtonPressed( sf::Mouse::Left ) && m_prevMouseDown == false)
		{
			window.close( );
		}

		if (playButton.checkIntersection( mousePosition ) && sf::Mouse::isButtonPressed( sf::Mouse::Left ) && m_prevMouseDown == false)
		{
			m_scoreManager->resetScore( );
			return EntityData::gameState::playing;
		}

		break;

	case UIManager::menuState::credits:
		//checks if back to menu button is intersected by mouse & left button is pressed - returns mainOptions if it is
		if (backToMainMenuButton.checkIntersection( mousePosition ) && sf::Mouse::isButtonPressed( sf::Mouse::Left ) && m_prevMouseDown == false)
		{
			state = menuState::mainOptions;
		}

		break;
	case UIManager::menuState::highScores:
		break;

	}

	//stores last mouse state (prevents button from being pressed more than once per down / up click)
	m_prevMouseDown = sf::Mouse::isButtonPressed( sf::Mouse::Left );
	//if nothing else has been returned, return mainMenu state to Game
	return EntityData::gameState::mainMenu;
	
}

void UIManager::drawMainMenu( sf::RenderWindow & window )
{	
	switch (state)
	{
	case UIManager::menuState::mainOptions:
		//if in main options window, draw all buttons / text elements
		playButton.draw( window );
		window.draw( m_mainMenuText );
		easyButton.draw( window );
		normalButton.draw( window );
		hardButton.draw( window );

		creditMenuButton.draw( window );
		exitButton.draw( window );
		break;

	case UIManager::menuState::credits:
		//if in credits window, draw credits text & menu button 
		window.draw( m_credits );
		backToMainMenuButton.draw( window );

		break;
	case UIManager::menuState::highScores:
		break;
	default:
		break;
	}

}

//updates game over menus
EntityData::gameState UIManager::updateGameOverMenu( EntityData::gameState GameState, sf::RenderWindow& window )
{
	//stores mouse position
	sf::Vector2i mousePosition = sf::Mouse::getPosition( window );

	switch (GameState)
	{
	case EntityData::gameState::playerDead:
	case EntityData::gameState::levelFailed:
		//same menu for player dead and level failed states - restart game or exit to main menu
		if (retry.checkIntersection( mousePosition ) && sf::Mouse::isButtonPressed( sf::Mouse::Left ))
		{
			//if retry button pressed, restart game
			m_scoreManager->resetScore( );
			m_prevMouseDown = true;
			return EntityData::gameState::playing;
		}

		break;

	case EntityData::gameState::levelComplete:
		if(nextLevel.checkIntersection( mousePosition ) && sf::Mouse::isButtonPressed( sf::Mouse::Left ))
		{
			//if next stage button pressed, restart game but keep current score
			m_prevMouseDown = true;
			return EntityData::gameState::playing;
		}

		break;

	default:
		break;
	}

	//back to menu button drawn in all 3 states

	if (backToMainMenuButton.checkIntersection( mousePosition ) && sf::Mouse::isButtonPressed( sf::Mouse::Left ) && m_prevMouseDown == false)
	{
		//if pressed, go to main menu
		m_scoreManager->resetScore( );
		m_prevMouseDown = true;
		state = menuState::mainOptions;
		return EntityData::gameState::mainMenu;
	}
	//flags last frames button input
	m_prevMouseDown = sf::Mouse::isButtonPressed( sf::Mouse::Left );

	//if no button is pressed, return the state passed originally
	return GameState;
}


void UIManager::drawGameOverMenu( EntityData::gameState GameState, sf::RenderWindow & window )
{
	switch (GameState)
	{

	case EntityData::gameState::playerDead:
	case EntityData::gameState::levelFailed:
		//draws "game over" background
		window.draw( gameOverMenuBackground );
		retry.draw( window );

		break;

	case EntityData::gameState::levelComplete:
		//draws "next level" background
		window.draw( levelCompleteMenuBackground );
		nextLevel.draw( window );

		break;
	}

	//checks if new high score was achieved
	if (m_scoreManager->returnNewHighScore( ))
	{
		m_highScore.setText( std::to_string(m_scoreManager->returnHighScore()) );
		window.draw( m_newHighScore );
		window.draw( m_highScore );
	}
	//draws back to menu button
	backToMainMenuButton.draw( window );
}

