#include "HeartManager.h"


HeartManager* HeartManager::sInstance = nullptr;

HeartManager* HeartManager::Instance() {
	if (sInstance == nullptr) {
		sInstance = new HeartManager();
	}

	return sInstance;
}

void HeartManager::Release() {

	delete sInstance;
	sInstance = nullptr;

}


void HeartManager::Update() {

	for (int i = 0; i < MAX_HEARTS; ++i) {
		mHearts[i]->Update();
	}

}

void HeartManager::Render() {

	for (int i = 0; i < MAX_HEARTS; ++i) {
		mHearts[i]->Render();
	}

}

void HeartManager::SpawnHeart(Vector2 pos) {
	for (int i = 0; i < MAX_HEARTS; ++i) {
		if (!mHearts[i]->Active()) {
			mHearts[i]->Spawn(pos);
			break;
		}
	}
}

void HeartManager::ClearHearts() {
	for (int i = 0; i < MAX_HEARTS; ++i) {
		mHearts[i]->Active(false);
	}
}




HeartManager::HeartManager() {

	for (int c = 0; c < MAX_HEARTS; c++) {
		mHearts[c] = new Heart();
	}

}

HeartManager::~HeartManager() {

	for (int c = 0; c < MAX_HEARTS; c++) {
		delete mHearts[c];
		mHearts[c] = nullptr;
	}

}