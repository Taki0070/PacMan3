#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/CsvReader.h"

namespace
{
	//const int STAGE_X{ 15 };
	//const int STAGE_Y{ 15 };
	/*const int sArray[STAGE_Y][STAGE_X]{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};*/
}

bool Stage::IsWall(int _x, int _y)
{

	if (stageData_[_y][_x] == STAGE_OBJ::WALL ) 
	{
		return true;
	}
	else
	return false;
}

Stage::Stage(GameObject* parent)
	:GameObject(parent, "Stage")
{
	CsvReader csv;
	csv.Load("map2.csv");

	stageWidth_ = csv.GetWidth();
	stageHight_ = csv.GetHeight();
	
	
	for (int i = 0; i < stageHight_; i++)
	{
		vector<int> sdata(stageWidth_, 0);
		stageData_.push_back(sdata);
	}
	for (int j = 0; j < stageHight_; j++)
	{
		for (int i = 0; i < stageWidth_; i++)
		{
			stageData_[j][i] = csv.GetValue(i, j);
		}
	}
}

void Stage::Initialize()
{
	hFloor_ = Model::Load("Model\\Floor.fbx");
	assert(hFloor_ >= 0);
	hBlock_ = Model::Load("Model\\Wall.fbx");
	assert(hBlock_ >= 0);

	Camera::SetPosition({ 6.5, 10, -3 });
	Camera::SetTarget({ 6.5, 0, 5.5 });

}

void Stage::Update()
{

}

void Stage::Draw()
{
	Transform floorTrans;
	floorTrans.position_ = { 0,0,0 };

	for (int z = 0; z < stageHight_; z++) {
		for (int x = 0; x < stageWidth_; x++) {
			floorTrans.position_ = { (float)x, 0, (float)(14 - z) };
			//if (x == 0 || z == 0 || x == 14 || z == 14) {
			//	Model::SetTransform(hBlock_, floorTrans);
			//	Model::Draw(hBlock_);
			//}
			//else {
			//	Model::SetTransform(hFloor_, floorTrans);
			//	Model::Draw(hFloor_);
			//}
			if (stageData_[z][x] == 1)
			{
				Model::SetTransform(hBlock_, floorTrans);
				Model::Draw(hBlock_);
			}
			else
			{
				Model::SetTransform(hFloor_, floorTrans);
				Model::Draw(hFloor_);
			}
		}
	}
}

void Stage::Release()
{
	//配列をクリア
	for (int i = 0; i < stageHight_; i++)
	{
		stageData_[i].clear();

	}
	stageData_.clear();
}