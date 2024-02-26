#pragma once
#include"Engine/GameObject.h"

class TITLE_SCENE
	:public GameObject
{
private:
	int hPict_;
	int hModel_;

public:
	TITLE_SCENE(GameObject* parent);

	void Initialize() override;


	void Update() override;

	void Draw() override;

	void Release() override;


};

