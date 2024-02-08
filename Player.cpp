#include "Player.h"
#include "Stage.h"
#include "Gauge.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"

namespace 
{
	const float PLAYER_MOVE_SPEED{ 0.2f };
}


Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), hModel_(-1), speed_(PLAYER_MOVE_SPEED),pStage_(nullptr)
	,hpCrr_(100),hpMax_(100)
{
}

void Player::Initialize()
{
	hModel_ = Model::Load("Model\\Player.fbx");
	assert(hModel_ >= 0);
	transform_.position_.x = 0.5;
	transform_.position_.z = 1.5;
	pStage_ = (Stage *)FindObject("Stage");//規定は アップキャストorダウンキャスト

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

	if (Input::IsKey(DIK_UP))
	{
		move = XMVECTOR{ 0, 0, 1, 0 };
		//moveDir = Dir::UP;
	}
	if (Input::IsKey(DIK_LEFT))
	{
		move = XMVECTOR{ -1, 0, 0, 0 };
		//moveDir = Dir::LEFT;
	}
	if (Input::IsKey(DIK_DOWN))
	{
		move = XMVECTOR{ 0, 0, -1, 0 };
		//moveDir = Dir::DOWN;
	}
	if (Input::IsKey(DIK_RIGHT))
	{
		move = XMVECTOR{ 1, 0, 0, 0 };
		//moveDir = Dir::RIGHT;
	}


	XMVECTOR pos = XMLoadFloat3(&(transform_.position_));
	XMVECTOR posTmp = XMVectorZero(); //すべてゼロ
	posTmp = pos + speed_ * move;

	int tx, ty;
	tx = (int)(XMVectorGetX(posTmp) + 1.0f);
	ty = pStage_->GetStageWidth() - (int)(XMVectorGetZ(posTmp) + 1.0f);
	if (!(pStage_->IsWall(tx, ty)))
	{
		pos = posTmp;
	}
	else
	{
		hpCrr_ = hpCrr_ - 2;
		if (hpCrr_ < 0)
		{
			hpCrr_ = 0;
		}
	}
	/*Debug::Log("(X,Z)=");
	Debug::Log(XMVectorGetX(pos));
	Debug::Log(",");
	Debug::Log(XMVectorGetZ(pos), true);

	Debug::Log("(iX,iZ)=");
	Debug::Log(tx);
	Debug::Log(",");
	Debug::Log(ty);
	Debug::Log(" : ");
	Debug::Log(pStage_->IsWall(tx, ty), true);*/
	

	if (!XMVector3Equal(move, XMVectorZero())) {
		XMStoreFloat3(&(transform_.position_), pos);
		//XMMATRIX rot = XMMatrixRotationY(-XM_PIDIV2); // π/2 ＝　90°
		//XMVECTOR modifiedVec = XMPlaneTransform(move, rot);
		//Debug::Log(XMVectorGetX(modifiedVec));
		//Debug::Log(",");
		//Debug::Log(XMVectorGetZ(modifiedVec));

		float angle = atan2(XMVectorGetX(move), XMVectorGetZ(move));
		Debug::Log("=>");
		Debug::Log(XMConvertToDegrees(angle), true);
	
		//XMVECTOR vdot = XMVector3Dot(vFront, move);
		//assert(XMVectorGetX(vdot) <= 1 && XMVectorGetX(vdot) >= -1);
		////float angle = acos(XMVectorGetX(vdot));
		//float angle = atan2(XMVectorGetX(move), XMVectorGetZ(move));

		/*XMVECTOR vCross = XMVector3Cross(vFront, move);
		if (XMVectorGetY(vCross) < 0)
		{
			angle *= -1;
		}*/

		transform_.rotate_.y = XMConvertToDegrees(angle);
	}
	Gauge* Gau = (Gauge*)FindObject("Gauge"); // インスタンス→Find	を見つける
	Gau->SetGaugeVal(hpCrr_, hpMax_);
}

void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Player::Release()
{
}