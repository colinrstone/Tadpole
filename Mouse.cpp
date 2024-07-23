#include "Mouse.h"

Mouse& Mouse::Instance() {
	static Mouse instance;
	return instance;
}

Mouse::Mouse() {

	mTimer = Timer::Instance();
	mInput = InputManager::Instance();

	mVisible = true;

	mScore = 0;
	mLives = 0;

	mMouseAnimate = NULL;
	mIsAnimating = false;

	mMouseRunDown = new AnimatedTexture("mouserundown.png", 0, 0, 32, 32, 1, 1, AnimatedTexture::vertical);
	mMouseRunDown->Parent(this);
	mMouseRunDown->Pos(local);

	mMouseRunUp = new AnimatedTexture("mouserunup.png", 0, 0, 32, 32, 1, 1, AnimatedTexture::vertical);
	mMouseRunUp->Parent(this);
	mMouseRunUp->Pos(local);

	mMouseRunRight = new AnimatedTexture("mouserunright.png", 0, 0, 32, 32, 1, 1, AnimatedTexture::vertical);
	mMouseRunRight->Parent(this);
	mMouseRunRight->Pos(local);

	mMouseRunLeft = new AnimatedTexture("mouserunleft.png", 0, 0, 32, 32, 1, 1, AnimatedTexture::vertical);
	mMouseRunLeft->Parent(this);
	mMouseRunLeft->Pos(local);

	mMouseIdle = new AnimatedTexture("mouseidledown.png", 0, 0, 32, 32, 1, 1, AnimatedTexture::vertical);
	mMouseIdle->Parent(this);
	mMouseIdle->Pos(local);

	mMouseIdleUp = new AnimatedTexture("mouseidleup.png", 0, 0, 32, 32, 1, 1, AnimatedTexture::vertical);
	mMouseIdleUp->Parent(this);
	mMouseIdleUp->Pos(local);

	mMouseIdleDown = new AnimatedTexture("mouseidledown.png", 0, 0, 32, 32, 1, 1, AnimatedTexture::vertical);
	mMouseIdleDown->Parent(this);
	mMouseIdleDown->Pos(local);

	mMouseIdleLeft = new AnimatedTexture("mouseidleleft.png", 0, 0, 32, 32, 1, 1, AnimatedTexture::vertical);
	mMouseIdleLeft->Parent(this);
	mMouseIdleLeft->Pos(local);

	mMouseIdleRight = new AnimatedTexture("mouseidleright.png", 0, 0, 32, 32, 1, 1, AnimatedTexture::vertical);
	mMouseIdleRight->Parent(this);
	mMouseIdleRight->Pos(local);

	mIsInteracting = false;

	mInteractionRange = 10.0f;

	mMouseInteractDown = new AnimatedTexture("mouseinteractdown.png", 0, 0, 11, 21, 1, 1, AnimatedTexture::vertical);
	mMouseInteractDown->Parent(this);
	mMouseInteractDown->Pos(local);

	mMouseInteract = mMouseInteractDown;

	mMouseInteractUp = new AnimatedTexture("mouseinteractup.png", 0, 0, 32, 32, 1, 1, AnimatedTexture::vertical);
	mMouseInteractUp->Parent(this);
	mMouseInteractUp->Pos(local);

	mMouseInteractRight = new AnimatedTexture("mouseinteractright.png", 0, 0, 32, 32, 1, 1, AnimatedTexture::vertical);
	mMouseInteractRight->Parent(this);
	mMouseInteractRight->Pos(local);

	mMouseInteractLeft = new AnimatedTexture("mouseinteractleft.png", 0, 0, 11, 32, 1, 1, AnimatedTexture::vertical);
	mMouseInteractLeft->Parent(this);
	mMouseInteractLeft->Pos(local);

	mInteractionTimer = 0.0f;
	mInteractionTimerInterval = 0.10f;

	mSetIdleDelayTimer = 0.0f;
	mSetIdleDelayTimerInterval = 0.1f;


}

Mouse::~Mouse() {

	mTimer = NULL;
	mInput = NULL;

	delete mMouseIdle;
	mMouseIdle = NULL;
}

void Mouse::HandleMovement()  {

	if (mInput->KeyDown(SDL_SCANCODE_RIGHT)) {

		mMouseAnimate = mMouseRunRight;
		mMouseIdle = mMouseIdleRight;
		mIsAnimating = true;
		//return Vector2(-1,0);

	}

	if (mInput->KeyDown(SDL_SCANCODE_LEFT)) {

		mMouseAnimate = mMouseRunLeft;
		mMouseIdle = mMouseIdleLeft;
		mIsAnimating = true;
		//return Vector2(1,0);
	}

	if (mInput->KeyDown(SDL_SCANCODE_UP)) {

		mMouseAnimate = mMouseRunUp;
		mMouseIdle = mMouseIdleUp;
		mIsAnimating = true;
		//return Vector2(0,1);
	}

	if (mInput->KeyDown(SDL_SCANCODE_DOWN)) {

		mMouseAnimate = mMouseRunDown;
		mMouseIdle = mMouseIdleDown;
		mIsAnimating = true;
		//return Vector2(0,-1);

	}
	
}


void Mouse::HandleInteract() {

	if (mInput->KeyDown(SDL_SCANCODE_SPACE) && !mIsInteracting) {
		mInteractionTimer = 0.0f;
		mIsInteracting = true;

	}

	if (mIsInteracting) {
		mInteractionTimer += mTimer->DeltaTime();


		// Perform the interacting behavior for the specified time interval
		if (mInteractionTimer < mInteractionTimerInterval) {

			if (mMouseIdle == mMouseIdleRight) {

				mMouseInteract = mMouseInteractRight;
				//printf("test");

			}
			else if (mMouseIdle == mMouseIdleLeft) {

				mMouseInteract = mMouseInteractLeft;
				//printf("test");
			}
			else if (mMouseIdle == mMouseIdleUp) {

				mMouseInteract = mMouseInteractUp;
				//printf("test");
			}
			else if (mMouseIdle == mMouseIdleDown) {

				mMouseInteract = mMouseInteractDown;
				//printf("test");
			}





		}
		else {

			// End the attack after the time interval has passed
			mIsInteracting = false;
			//mMouseInteract = NULL;
		}
	}






}




Vector2 Mouse::GetPosition() const {

	return mMousePosition;
}

float Mouse::GetInteractionRange() const {

	return mInteractionRange;
}

void Mouse::SetMouseIdle() {


	mSetIdleDelayTimer += mTimer->DeltaTime();

	if (mSetIdleDelayTimer > mSetIdleDelayTimerInterval) {

		mIsInteracting = false;
		mIsAnimating = false;

		mSetIdleDelayTimer = 0.0f;

	}

}


void Mouse::Visible(bool visible) {

	mVisible = visible;

}


int Mouse::Score() {

	return mScore;
}

int Mouse::Lives() {

	return mLives;
}


void Mouse::AddScore(int change) {

	mScore += change;
}


/*
void Mouse::SetMousePosition(float x, float y) {

	mMousePosition.x = x;
	mMousePosition.y = y;

}

void Mouse::SetMousePosition(const Vector2& position) {

	mMousePosition = position;

}
*/


void Mouse::Update() {

	HandleInteract();
	HandleMovement();

	if (mMouseInteract)
		mMouseInteract->Update();

	if (mMouseAnimate)
		mMouseAnimate->Update();

	mMouseIdle->Update();

	int x = mMousePosition.x;
	int y = mMousePosition.y;

	//printf(" %i", x);
	//printf(",%i" , y);

	//if (mInput->KeyPressed(SDL_SCANCODE_P)) {
	//	int x = static_cast<int>(mMousePosition.x);
	//	int y = static_cast<int>(mMousePosition.y);
	//	printf("Mouse Position: (%i, %i)\n", x, y);
	//}

}


void Mouse::Render() {

	if (mIsInteracting)
		mMouseInteract->Render();
	else if (mIsAnimating)
		mMouseAnimate->Render();
	else
		mMouseIdle->Render();

}

