#include "Cat.h"

Cat& Cat::Instance() {
	static Cat instance;
	return instance;
}

Cat::Cat() {

	mTimer = Timer::Instance();
	mInput = InputManager::Instance();

	mVisible = true;

	mCatAnimate = NULL;
	mIsAnimating = false;

	mCatRunDown = new AnimatedTexture("catrundown.png", 0, 0, 32, 32, 1, 1, AnimatedTexture::vertical);
	mCatRunDown->Parent(this);
	mCatRunDown->Pos(local);

	mCatRunUp = new AnimatedTexture("catrunup.png", 0, 0, 32, 32, 1, 1, AnimatedTexture::vertical);
	mCatRunUp->Parent(this);
	mCatRunUp->Pos(local);

	mCatRunRight = new AnimatedTexture("catrunright.png", 0, 0, 32, 32, 1, 1, AnimatedTexture::vertical);
	mCatRunRight->Parent(this);
	mCatRunRight->Pos(local);

	mCatRunLeft = new AnimatedTexture("catrunleft.png", 0, 0, 32, 32, 1, 1, AnimatedTexture::vertical);
	mCatRunLeft->Parent(this);
	mCatRunLeft->Pos(local);

	mCatIdle = new AnimatedTexture("catidledown.png", 0, 0, 32, 32, 1, 1, AnimatedTexture::vertical);
	mCatIdle->Parent(this);
	mCatIdle->Pos(local);

	mCatIdleUp = new AnimatedTexture("catidleup.png", 0, 0, 32, 32, 1, 1, AnimatedTexture::vertical);
	mCatIdleUp->Parent(this);
	mCatIdleUp->Pos(local);

	mCatIdleDown = new AnimatedTexture("catidledown.png", 0, 0, 32, 32, 1, 1, AnimatedTexture::vertical);
	mCatIdleDown->Parent(this);
	mCatIdleDown->Pos(local);

	mCatIdleLeft = new AnimatedTexture("catidleleft.png", 0, 0, 32, 32, 1, 1, AnimatedTexture::vertical);
	mCatIdleLeft->Parent(this);
	mCatIdleLeft->Pos(local);

	mCatIdleRight = new AnimatedTexture("catidleright.png", 0, 0, 32, 32, 1, 1, AnimatedTexture::vertical);
	mCatIdleRight->Parent(this);
	mCatIdleRight->Pos(local);

	mIsInteracting = false;

	mInteractionRange = 10.0f;

	mCatInteractDown = new AnimatedTexture("catinteractdown.png", 0, 0, 11, 21, 1, 1, AnimatedTexture::vertical);
	mCatInteractDown->Parent(this);
	mCatInteractDown->Pos(local);

	mCatInteract = mCatInteractDown;

	mCatInteractUp = new AnimatedTexture("catinteractup.png", 0, 0, 32, 32, 1, 1, AnimatedTexture::vertical);
	mCatInteractUp->Parent(this);
	mCatInteractUp->Pos(local);

	mCatInteractRight = new AnimatedTexture("catinteractright.png", 0, 0, 32, 32, 1, 1, AnimatedTexture::vertical);
	mCatInteractRight->Parent(this);
	mCatInteractRight->Pos(local);

	mCatInteractLeft = new AnimatedTexture("catinteractleft.png", 0, 0, 11, 32, 1, 1, AnimatedTexture::vertical);
	mCatInteractLeft->Parent(this);
	mCatInteractLeft->Pos(local);

	mInteractionTimer = 0.0f;
	mInteractionTimerInterval = 0.10f;

	mSetIdleDelayTimer = 0.0f;
	mSetIdleDelayTimerInterval = 0.1f;


}

Cat::~Cat() {

	mTimer = NULL;
	mInput = NULL;

	delete mCatIdle;
	mCatIdle = NULL;
}

void Cat::CalculateDistance() {





}


void Cat::HandleMovement() {

	
}

Vector2 Cat::GetPosition() const {

	return mCatPosition;
}

float Cat::GetInteractionRange() const {

	return mInteractionRange;
}

void Cat::SetCatIdle() {


	mSetIdleDelayTimer += mTimer->DeltaTime();

	if (mSetIdleDelayTimer > mSetIdleDelayTimerInterval) {

		mIsInteracting = false;
		mIsAnimating = false;

		mSetIdleDelayTimer = 0.0f;

	}

}

void Cat::Visible(bool visible) {

	mVisible = visible;

}

/*
void Cat::SetCatPosition(float x, float y) {

	mCatPosition.x = x;
	mCatPosition.y = y;

}

void Cat::SetCatPosition(const Vector2& position) {

	mCatPosition = position;

}
*/

void Cat::Update() {

	HandleMovement();

	if (mCatAnimate)
		mCatAnimate->Update();

	mCatIdle->Update();

	//int x = mCatPosition.x;
	//int y = mCatPosition.y;

	//printf(" %i", x);
	//printf(",%i" , y);

	//if (mInput->KeyPressed(SDL_SCANCODE_P)) {
	//	int x = static_cast<int>(mCatPosition.x);
	//	int y = static_cast<int>(mCatPosition.y);
	//	printf("Cat Position: (%i, %i)\n", x, y);
	//}

}

void Cat::Render() {

	if (mIsAnimating)
		mCatAnimate->Render();
	else
		mCatIdle->Render();

}

