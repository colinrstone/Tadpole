#include "SideBar.h"


SideBar::SideBar() {


	//mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	mBottomBackground = new Texture("background.png");
	mBottomBackground->Parent(this);
	mBottomBackground->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.0f, Graphics::Instance()->SCREEN_HEIGHT * 0.90));
	mBottomBackground->Scale(Vector2(20.0f, 1.0f));


	mTopBackground = new Texture("topbackground.png");
	mTopBackground->Parent(this);
	mTopBackground->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.0f, -22.0f));
	mTopBackground->Scale(Vector2(20.0f, 2.0f));


	mBlackStageBackground = new Texture("blackstagebackground.png");
	mBlackStageBackground->Parent(this);
	mBlackStageBackground->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.50));
	mBlackStageBackground->Scale(Vector2(20.0f, 20.0f));


	mLeftSideBackground = new Texture("leftsidebackground.png");
	mLeftSideBackground->Parent(this);
	mLeftSideBackground->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.0f, Graphics::Instance()->SCREEN_HEIGHT * 0.00));

	mRightSideBackground = new Texture("rightsidebackground.png");
	mRightSideBackground->Parent(this);
	mRightSideBackground->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 1.0f, Graphics::Instance()->SCREEN_HEIGHT * 0.1f));

}

SideBar::~SideBar() {

	//mTimer = NULL;
	mAudio = NULL;

	delete mBottomBackground;
	mBottomBackground = NULL;

	delete mTopBackground;
	mTopBackground = NULL;

	delete mBlackStageBackground;
	mBlackStageBackground = NULL;
	delete mLeftSideBackground;
	mLeftSideBackground = NULL;
	delete mRightSideBackground;
	mRightSideBackground = NULL;

}


void SideBar::Update() {

}

void SideBar::Render() {

	mBlackStageBackground->Render();
	mLeftSideBackground->Render();
	mRightSideBackground->Render();
	mBottomBackground->Render();
	//mTopBackground->Render();


}
