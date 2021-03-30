#include "DifficultyData.h"

//namespace storing gameplay values for each game difficulty
namespace difficulty
{
	//stores enum val. of current difficulty
	difficultySetting currentDifficultyEnum;

	//arrays of difficulty data (3 entries due to there being 3 difficulties)
	int playerBulletCount[ 3 ];
	int playerLives[ 3 ];
	float enemyProjSpeed[ 3 ];
	float enemySpeedIncrease[ 3 ];
	int enemyRows[ 3 ];
	int enemyScoreIncrease[ 3 ];
	
	//func. allows data to be assigned (would not let me do it without func. called at run-time, got "already defined" error)
	void setupDifficultyData( )
	{
		playerBulletCount[ 0 ] = 3;
		playerBulletCount[ 1 ] = 2;
		playerBulletCount[ 2 ] = 1;

		playerLives[ 0 ] = 4;
		playerLives[ 1 ] = 3;
		playerLives[ 2 ] = 2;

		enemyProjSpeed[ 0 ] = 350.f;
		enemyProjSpeed[ 1 ] = 400.f;
		enemyProjSpeed[ 2 ] = 550.f;

		enemySpeedIncrease[ 0 ] = 1.5f;
		enemySpeedIncrease[ 1 ] = 2.f;
		enemySpeedIncrease[ 2 ] = 3.f;

		enemyRows[ 0 ] = 4;
		enemyRows[ 1 ] = 5;
		enemyRows[ 2 ] = 6;

		enemyScoreIncrease[ 0 ] = 2;
		enemyScoreIncrease[ 1 ] = 5;
		enemyScoreIncrease[ 2 ] = 8;

		//current difficulty defaults to normal, can be changed and referenced from other scripts as needed
		currentDifficultyEnum = difficulty::difficultySetting::Normal;
	}

	//IMPROVEMENTS: put all data into 2D vector array, map each array in said 2D array w/ a var. to change (e.g. difficultyVars[enemyScoreIncrease] = 2DVector[6])
}

