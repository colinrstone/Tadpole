#ifndef Town_h
#define Town_h
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"


#include "TerrainGrid.h"
#include "FloodGrid.h"


#include "Mouse.h"
#include <list>
#include <utility>

#include "Cat.h"

#include "RainEffect.h"
#include "Car.h"


using namespace QuickSDL;

class Town : public GameEntity {

public:

	enum LEVEL_STATES { running, finished, gameover };

	LEVEL_STATES mCurrentState;
	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

	bool mNewTownStarted;
	Texture* mStageBackground;	

	int mTargetedGrid[27][13];
	int mTargetedGridOriginRow;
	int mTargetedGridOriginColumn;

	TerrainGrid* mTerrainGrid;
	int** mTerrainValues;

	FloodGrid* mFloodGrid;
	int** mFloodValues;

	Mouse* mMouse;
	int mMousePositionX;
	int mMousePositionY;

	Cat* mCat;

	int mMoveDirectionX;
	int mMoveDirectionY;

	std::list<std::pair<int, int>> pushedBlocks;

	RainEffect* mRainEffect;
	Car* mCar;

private:

	int mTileRows;
	int mTileColumns;

private:

public:

	Town();
	~Town();
	
	LEVEL_STATES State();

	//RNG
	int RandomVertical(void);
	int RandomHorizontal(void);
	int RandomCount(int count);
	int RandomFiftyFifty(void);

	void LoadInitialGrids(int stageNumber);
	void LoadInitialValues(int stageNumber);

	void LoadGrids();
	void LoadTargetedGrid();
	void HandleTargetScreenTiles();

	void DrawGrids();

	void HandleEvent();
	//void HandleBlockPush(int row, int column);
	void Move(int dx, int dy);

	void Update();
	void Render();


};

#endif /* Town_h */
