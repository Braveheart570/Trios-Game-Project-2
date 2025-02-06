#pragma once
#include "Heart.h"

class HeartManager {

public:

	static HeartManager* Instance();
	static void Release();

	void Render();
	void Update();

	void SpawnHeart(Vector2 pos);

	void ClearHearts();

private:

	static HeartManager* sInstance;

	static const int MAX_HEARTS = 4;
	Heart* mHearts[MAX_HEARTS];

	HeartManager();
	~HeartManager();

};