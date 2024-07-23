#include "Town.h"


Town::Town() {

	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	//Initialize the background imagery
	mStageBackground = NULL;

	//Targeted
	mTargetedGridOriginRow = 0;
	mTargetedGridOriginColumn = 0;

	//Arrays that hold values of grids
	mTerrainGrid = NULL;
	mFloodGrid = NULL;

	mMousePositionX = Graphics::Instance()->SCREEN_WIDTH * 0.505;
	mMousePositionY = Graphics::Instance()->SCREEN_HEIGHT * 0.415;
	mMouse = new Mouse();
	mMouse->Pos(Vector2(mMousePositionX, mMousePositionY));

	mMoveDirectionX = 0;
	mMoveDirectionY = 0;
	

	mRainEffect = NULL;
	mCar = NULL;
}

Town::~Town() {

	mTimer = NULL;
	mInput = NULL;
	mAudio = NULL;

	mStageBackground = NULL;
	delete mTargetedGrid;
	mTargetedGridOriginRow = NULL;
	mTargetedGridOriginColumn = NULL;
	mTerrainGrid = NULL;
	mFloodGrid = NULL;

	mMousePositionX = NULL;
	mMousePositionY = NULL;
	mMouse = NULL;

	mMoveDirectionX = NULL;
	mMoveDirectionY = NULL;

	mRainEffect = NULL;
	mCar = NULL;
}

Town::LEVEL_STATES Town::State() {
	return mCurrentState;
}

int Town::RandomVertical(void) {

	std::random_device os_seed;
	const u32 seed = os_seed();

	engine generator(seed);
	std::uniform_int_distribution< u32 > distribute(1, 15);

	for (int repetition = 0; repetition < 10; ++repetition)
		//std::cout << distribute(generator) << std::endl;
		return distribute(generator);
}

int Town::RandomHorizontal(void) {

	std::random_device os_seed;
	const u32 seed = os_seed();

	engine generator(seed);
	std::uniform_int_distribution< u32 > distribute(1, 24);

	for (int repetition = 0; repetition < 10; ++repetition)
		//std::cout << distribute(generator) << std::endl;
		return distribute(generator);
}

int Town::RandomCount(int count) {

	std::random_device os_seed;
	const u32 seed = os_seed();

	engine generator(seed);
	std::uniform_int_distribution< u32 > distribute(0, (count - 1));

	for (int repetition = 0; repetition < 10; ++repetition)
		//std::cout << distribute(generator) << std::endl;
		return distribute(generator);
}

int Town::RandomFiftyFifty(void) {

	std::random_device os_seed;
	const u32 seed = os_seed();

	engine generator(seed);
	std::uniform_int_distribution< u32 > distribute(0, 1);

	for (int repetition = 0; repetition < 10; ++repetition)
		//std::cout << distribute(generator) << std::endl;
		return distribute(generator);
}

void Town::LoadInitialValues(int stageNumber) {

	//Allocate memory for size of grid
	switch (stageNumber)
	{
	case 0:
		break;
	case 1:
		mTileRows = 28;
		mTileColumns = 17;

		mTerrainValues = new int* [mTileRows];
		for (int i = 0; i < mTileRows; ++i) {
			mTerrainValues[i] = new int[mTileColumns];
		}

		mFloodValues = new int* [mTileRows];
		for (int i = 0; i < mTileRows; ++i) {
			mFloodValues[i] = new int[mTileColumns];
		}
		break;
	case 2:
		mTileRows = 56;
		mTileColumns = 23;

		mTerrainValues = new int* [mTileRows];
		for (int i = 0; i < mTileRows; ++i) {
			mTerrainValues[i] = new int[mTileColumns];
		}

		mFloodValues = new int* [mTileRows];
		for (int i = 0; i < mTileRows; ++i) {
			mFloodValues[i] = new int[mTileColumns];
		}
		break;
	default:
		break;
	}

	//Begin retreiving values
	for (int row = 0; row < mTileRows; row++)
	{
		for (int column = 0; column < mTileColumns; column++)
		{
			mTerrainValues[row][column] = mTerrainGrid->GetValuesTerrainGrid(row, column, stageNumber);
			mFloodValues[row][column] = mFloodGrid->GetValuesFloodGrid(row, column, stageNumber);

		}
	}



}

void Town::LoadInitialGrids(int stageNumber) {

	//create new
	mTerrainGrid = new TerrainGrid();
	mFloodGrid = new FloodGrid();

	//need a function that sets mTerrainValue to the static variable on top of TerrainGrid.cpp
	LoadInitialValues(stageNumber);

	//Functions that take stage number and gather intital grid values
	mTerrainGrid->LoadInitialTerrainGrid(stageNumber, mTerrainValues);
	mFloodGrid->LoadInitialFloodGrid(stageNumber, mFloodValues);
}

void Town::LoadGrids() {
	 
	//Functions that pass new values of grids to be updated by their containers
	mTerrainGrid->Update(mTerrainValues, mTargetedGridOriginRow, mTargetedGridOriginColumn);
	mFloodGrid->Update(mFloodValues);
}

void Town::LoadTargetedGrid() {

	
	if (mTargetedGrid != nullptr) {
		for (int i = 0; i < mTileRows; ++i) {
			delete[] mTargetedGrid[i];
		}
		delete[] mTargetedGrid;
	}
	

	//int selectionX = mTargetedGridOriginRow + 28;
	//int selectionY = mTargetedGridOriginColumn + 12;

	for (int row = 0; row < 27; row++)
	{
		for (int column = 0; column < 13; column++)
		{
			int selectionX = row + mTargetedGridOriginRow;
			int selectionY = column + mTargetedGridOriginColumn;

			mTargetedGrid[row][column] = 0;
		}
	}

}

void Town::HandleTargetScreenTiles() {

	if (mInput->KeyPressed(SDL_SCANCODE_UP)) {
		if (mTargetedGridOriginColumn < mTileColumns - 13) {
			mTargetedGridOriginColumn++;
		}
	}
	else if (mInput->KeyPressed(SDL_SCANCODE_DOWN)) {
		if (mTargetedGridOriginColumn > 0) {
			mTargetedGridOriginColumn--;
		}
	}

	if (mInput->KeyPressed(SDL_SCANCODE_LEFT)) {
		if (mTargetedGridOriginRow < mTileRows - 27) {
			mTargetedGridOriginRow++;
		}
	}
	else if (mInput->KeyPressed(SDL_SCANCODE_RIGHT)) {
		if (mTargetedGridOriginRow > 0) {
			mTargetedGridOriginRow--;
		}
	}

}

void Town::DrawGrids() {

	//mTerrainGrid->DrawTerrainGrid();
	mTerrainGrid->Render(mTargetedGridOriginRow, mTargetedGridOriginColumn);
	mFloodGrid->Render();
}

void Town::HandleEvent() {

	if (mInput->KeyPressed(SDL_SCANCODE_UP)) {
		mMoveDirectionX = 0;
		mMoveDirectionY = 1;
	}
	else if (mInput->KeyPressed(SDL_SCANCODE_DOWN)) {
		mMoveDirectionX = 0;
		mMoveDirectionY = -1;

	}
	else if (mInput->KeyPressed(SDL_SCANCODE_LEFT)) {
		mMoveDirectionX = 1;
		mMoveDirectionY = 0;
	}
	else if (mInput->KeyPressed(SDL_SCANCODE_RIGHT)) {
		mMoveDirectionX = -1;
		mMoveDirectionY = 0;
	}
	else {
		mMoveDirectionX = 0;
		mMoveDirectionY = 0;
	}


}

void Town::Move(int dx, int dy) {

	printf("%i \n", dx);
	printf("%i \n \n", dy);
	const int newX = mTargetedGridOriginRow + 13 + mMoveDirectionX, newY = mTargetedGridOriginColumn + 6 + mMoveDirectionY;
	//printf("%i", newX);
	//printf("%i", newY);
	const int targetTerrainType = mTerrainValues[newX][newY];

	// Ground tile : move
	//if (targetTerrainType == 2)
		//mMoveDirectionX = newX, mMoveDirectionY = newY;

	// Block tile : move it if possible
	 if (targetTerrainType == 0)
	{
		int blockEndX = newX, blockEndY = newY;

		do {
			blockEndX += mMoveDirectionX, blockEndY += mMoveDirectionY;
			//printf("%i", blockEndX);
			//printf("%i", blockEndY);
		} while (mTerrainValues[blockEndX][blockEndY] == 0);
		if (mTerrainValues[blockEndX][blockEndY] != 2)
			return;

		mTerrainValues[newX][newY] = 2;
		mTerrainValues[blockEndX][blockEndY] = 0;

	}

}


void Town::Update() {

	//Timers


	//Loss conditions



	//Animations
	//character, dynamic tiles (floodwater)
	mMouse->Update();

	//Handle timing based events that check timers
	HandleEvent();
	Move(mMoveDirectionX, mMoveDirectionY);

	//Check and handle if the player selects the range of selections he can perform at a given time
	HandleTargetScreenTiles();

	//Check and handle if a player is placing an object from menu or using a move or action command on the board


	//Reload the grids with new information adjusted
	LoadGrids();
	//mCar->Update();



}

void Town::Render() {

	DrawGrids();
	//mCar->Render();
	mMouse->Render();

}

