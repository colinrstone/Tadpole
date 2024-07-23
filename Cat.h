#ifndef Cat_h
#define Cat_h
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"

#include "Camera.h"
#include "TerrainGrid.h"

using namespace QuickSDL;

class Cat : public GameEntity {

private:


	Timer* mTimer;
	InputManager* mInput;
	//AudioManager* mAudio;

	Vector2 mCatPosition;


	Texture* mCatIdle;
	Texture* mCatIdleUp;
	Texture* mCatIdleDown;
	Texture* mCatIdleLeft;
	Texture* mCatIdleRight;

	bool mIsAnimating;
	AnimatedTexture* mCatAnimate;

	AnimatedTexture* mCatRunUp;
	AnimatedTexture* mCatRunDown;
	AnimatedTexture* mCatRunLeft;
	AnimatedTexture* mCatRunRight;

	bool mIsInteracting;
	AnimatedTexture* mCatInteract;
	AnimatedTexture* mCatInteractUp;
	AnimatedTexture* mCatInteractDown;
	AnimatedTexture* mCatInteractLeft;
	AnimatedTexture* mCatInteractRight;
	float mInteractionTimer;
	float mInteractionTimerInterval;
	float mInteractionRange;

	float mSetIdleDelayTimer;
	float mSetIdleDelayTimerInterval;


	float mMoveSpeed;
	Vector2 mMoveLowerBounds;
	Vector2 mMoveUpperBounds;

	bool mVisible;

	int mScore;
	int mLives;


private:




public:

	Cat();
	~Cat();

	static Cat& Instance();

	void Visible(bool visible);

	int Score();
	int Lives();

	void AddScore(int change);

	Vector2 GetPosition() const;
	float GetInteractionRange() const;

	void CalculateDistance();
	void HandleMovement();

	void HandleBlockPush();
	void HandleInteract();

	void SetCatIdle();

	// Set the position of the object in the game world
	//void SetCatPosition(float x, float y);
	//void SetCatPosition(const Vector2& position);

	void Update();
	void Render();


};






#endif /* Cat_h */
