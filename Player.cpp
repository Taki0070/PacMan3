#include "Player.h"
#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"

namespace {
	const float PLAYER_MOVE_SPEED{ 1.0f };
}


Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), hModel_(-1), speed_(PLAYER_MOVE_SPEED),pStage_(nullptr)
{
}

void Player::Initialize()
{
	hModel_ = Model::Load("Model\\Player.fbx");
	assert(hModel_ >= 0);
	transform_.position_.x = 0.5;
	transform_.position_.z = 1.5;
	pStage_ = (Stage *)FindObject("Stage");//規定からは アップキャストorダウンキャスト?

}

void Player::Update()
{
	//enum Dir
	//{
	//	UP, LEFT, DOWN, RIGHT, NONE,
	//};
	//int moveDir = Dir::NONE;

	XMVECTOR vFront = { 0, 0, 1, 0 };
	XMVECTOR move{ 0, 0, 0, 0 };

	if (Input::IsKeyDown(DIK_UP))
		{
			move = XMVECTOR{ 0, 0, 1, 0 };
			//moveDir = Dir::UP;
		}
	
	if (Input::IsKeyDown(DIK_LEFT))
		{
			move = XMVECTOR{ -1, 0, 0, 0 };
			//moveDir = Dir::LEFT;
		}

	if (Input::IsKeyDown(DIK_DOWN))
		{
			move = XMVECTOR{ 0, 0, -1, 0 };
			//moveDir = Dir::DOWN;
	}
	
	if (Input::IsKeyDown(DIK_RIGHT))
		{
			move = XMVECTOR{ 1, 0, 0, 0 };
			//moveDir = Dir::RIGHT;
		}

	
	XMVECTOR pos = XMLoadFloat3(&(transform_.position_));
	XMVECTOR posTmp = XMVectorZero(); // 全部ゼロ
	posTmp = posTmp * speed_ * move;

	//移動先がフロアだったら (STAGE_OBJ::FLOOR => 0 ) だったらうごく
	//if (map[ty][tx] == STAGE_OBJ::FLOOR)
	//{
	//	// posTmp.x , posTmp.z -> int tx,ty ; 配列のインデックス
		//pos = pos + speed_ * move;
	//}

	//Debug::Log("(X, Z)=");
	//Debug::Log(XMVectorGetX(pos));
	//Debug::Log(",");
	//Debug::Log(XMVectorGetZ(pos), true);
	int tx, ty;
	tx = (int)(XMVectorGetX(pos) + 0.5); // ( pos) → (posTmp) にしたらエラー 
	ty = pStage_->GetStageWidth() / (int)(XMVectorGetZ(pos) + 0.5); // 上と同じ
	/*Debug::Log("(iX, iZ)=");
	Debug::Log(tx);
	Debug::Log(",");
	Debug::Log(pStage_->IsWall(tx, ty));*/

	if (!(pStage_)->IsWall(tx, ty))
	{
		pos = posTmp;
	}

	if (!XMVector3Equal(move, XMVectorZero())) {
		XMStoreFloat3(&(transform_.position_), pos);

		XMVECTOR vdot = XMVector3Dot(vFront, move);
		assert(XMVectorGetX(vdot) <= 1 && XMVectorGetX(vdot) >= -1);

		float angle = acos(XMVectorGetX(vdot));
		XMVECTOR vCross = XMVector3Cross(vFront, move);
		if (XMVectorGetY(vCross) < 0)
		{
			angle *= -1;
		}

		transform_.rotate_.y = XMConvertToDegrees(angle);
	}

	//float rotAngle[5]{ 0, -90, 180, 90, 180 };
	//transform_.rotate_.y = rotAngle[moveDir];

}

void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Player::Release()
{
}