#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include <fstream>

//handles player scores (reads from / writes to Scores.txt)
//
// ## NOTE ##
// A full score manager was written for my previous game, Snake Town
// Implementing it again seemed unnecessary, as it would be the same system (and I would likely not learn anything from doing it all over again)
// As such - this score management system is a little on the basic side. That is intentional.
//
class ScoreManager
{
private:
	//stores current running score
	int m_currentScore;
	//stores current / last high score reached
	int m_highScore;

	//read-type file used to read score
	std::ifstream m_scoreReadFile;
	//write-type file used to write new high score to Score.txt
	std::ofstream m_scoreWriteFile;

	bool m_newHighScore = false;

	//reads high score from Score.txt and saves it as m_highScore
	void fetchHighScore( );

public:
	//default constructor
	ScoreManager( );
	//destructor
	~ScoreManager( );
	
	//run when player score changes, updates value stored in m_currentScore
	void updateCurrentScore( int scoreIncrease );
	//compares m_currentScore with m_highScore
	void checkHighScore( );
	//if the current score > current high score, updates file & var.
	void setHighScore( int score );

	//GETTERS

	//returns the current score (used by UIManager)
	int returnCurrentScore( );
	//returns the high score stored in m_highScore (used by UIManager)
	int returnHighScore( );
	bool returnNewHighScore( );
	void resetScore( );
};

#endif // !SCOREMANAGER_H