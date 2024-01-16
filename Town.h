#ifndef Town_h
#define Town_h
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"
using namespace QuickSDL;

class Town : public GameEntity {

public:

	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

	Texture* mStageBackground;

	



private:

	int** mTileMap;
	int mTileRows;
	int mTileColumns;

private:



public:

	Town();
	~Town();




	void Update();
	void Render();


};

#endif /* Town_h */
