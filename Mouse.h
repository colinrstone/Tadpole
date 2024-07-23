#ifndef Mouse_h
#define Mouse_h
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"

#include "Camera.h"
#include "TerrainGrid.h"

using namespace QuickSDL;

class Mouse : public GameEntity {

private:


	Timer* mTimer;
	InputManager* mInput;
	//AudioManager* mAudio;

	Vector2 mMousePosition;


	Texture* mMouseIdle;
	Texture* mMouseIdleUp;
	Texture* mMouseIdleDown;
	Texture* mMouseIdleLeft;
	Texture* mMouseIdleRight;

	bool mIsAnimating;
	AnimatedTexture* mMouseAnimate;

	AnimatedTexture* mMouseRunUp;
	AnimatedTexture* mMouseRunDown;
	AnimatedTexture* mMouseRunLeft;
	AnimatedTexture* mMouseRunRight;

	bool mIsInteracting;
	AnimatedTexture* mMouseInteract;
	AnimatedTexture* mMouseInteractUp;
	AnimatedTexture* mMouseInteractDown;
	AnimatedTexture* mMouseInteractLeft;
	AnimatedTexture* mMouseInteractRight;
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

	Mouse();
	~Mouse();

	static Mouse& Instance();

	void Visible(bool visible);

	int Score();
	int Lives();

	void AddScore(int change);

	Vector2 GetPosition() const;
	float GetInteractionRange() const;

	void HandleMovement();
	void HandleBlockPush();
	void HandleInteract();

	void SetMouseIdle();

	// Set the position of the object in the game world
	//void SetMousePosition(float x, float y);
	//void SetMousePosition(const Vector2& position);

	void Update();
	void Render();


};






#endif /* Mouse_h */
