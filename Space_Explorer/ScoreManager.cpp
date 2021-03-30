#include <iostream>
#include <string>
#include "ScoreManager.h"

//manages player score
ScoreManager::ScoreManager( )
{
	//sets current score to 0
	m_currentScore = 0;
	//fetches high score from .txt file
	fetchHighScore( );
}

//destructor
ScoreManager::~ScoreManager( )
{
}

//saves high score from Scores.txt
void ScoreManager::fetchHighScore( )
{
	//opens file
	m_scoreReadFile.open( "Scores.txt" );
	//creates temp variable to store file output
	std::string scoreString;

	//reads line from file, stores as scoreString
	if (m_scoreReadFile.is_open( ))
	{
		getline( m_scoreReadFile, scoreString );

		//converts string to int value (e.g. "123" becomes 123)
		m_highScore = std::stoi( scoreString );
		//closes file
		m_scoreReadFile.close( );
	}
}


void ScoreManager::updateCurrentScore( int scoreIncrease )
{
	//increases score by [x] amount
	m_currentScore += scoreIncrease;
	checkHighScore( );
}

void ScoreManager::checkHighScore( )
{
	//compares current score to current highscore - if current score is more than high score, change high score to current score
	if (m_currentScore >= m_highScore)
	{
		m_highScore = m_currentScore;
		m_newHighScore = true;
		setHighScore( m_highScore );
	}
}

void ScoreManager::setHighScore( int score )
{
	//opens Scores.txt in write mode
	m_scoreWriteFile.open( "Scores.txt", std::ofstream::out );

	//converts current score to string
	std::string scoreString;
	scoreString = std::to_string( m_currentScore );

	//checks if file is already open, writes score to said file & closes it
	if (m_scoreWriteFile.is_open( ))
	{
		m_scoreWriteFile << scoreString;

		m_scoreWriteFile.close( );
	}
}

int ScoreManager::returnCurrentScore( )
{
	//returns current player score
	return m_currentScore;
}

int ScoreManager::returnHighScore( )
{
	//returns current high score
	return m_highScore;
}

bool ScoreManager::returnNewHighScore( )
{
	return m_newHighScore;
}

void ScoreManager::resetScore( )
{
	m_currentScore = 0;
	m_newHighScore = false;
}