#pragma once
#include"Engine/GameObject.h"
class pose_scene
	:public GameObject
{
private:
	int hPict_;
	int hModel_;

public:
	pose_scene(GameObject* parent);

	void Initialize() override;


	void Update() override;

	void Draw() override;

	void Release() override;


};

