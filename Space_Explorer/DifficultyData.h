#ifndef  DIFFICULTYDATA_H
#define DIFFICULTYDATA_H


//namespace containing data relating to difficulty settings
namespace difficulty
{
	//enum of different settings (currently 3, hence all arrays having 3 entries]
	enum class difficultySetting {
		Easy = 0,
		Normal = 1,
		Hard = 2
	};
	//int value associated with enum corrosponds to difficulty index in arrays below

	//ref. to "current" difficulty
	extern difficultySetting currentDifficultyEnum;

	
	
	//definitions of all difficulty-dependant values (stored as [number of difficulties] arrays)
	extern int playerBulletCount[ 3 ];
	extern int playerLives[ 3 ];
	extern int enemyRows[ 3 ];
	extern int enemyScoreIncrease[ 3 ];

	extern float enemyProjSpeed[ 3 ];
	extern float enemySpeedIncrease[ 3 ];

	//setupDifficultyData: calls func. to assign values to each difficulty "setting"
	void setupDifficultyData( );
}

#endif // ! DIFFICULTYDATA_H

