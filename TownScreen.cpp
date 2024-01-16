#include "TownScreen.h"

TownScreen::TownScreen() {

	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mStage = NULL;


}

TownScreen::~TownScreen() {

	mTimer = NULL;
	mInput = NULL;
	mAudio = NULL;


}


void TownScreen::StartNewTown() {

	mTown = new Town();

}


void TownScreen::Update() {


	mStage->Update();


}


void TownScreen::Render() {


	mStage->Render();



}
