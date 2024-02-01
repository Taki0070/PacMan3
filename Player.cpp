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
	pStage_ = (Stage *)FindObject("Stage");//�K�肩��� �A�b�v�L���X�gor�_�E���L���X�g?

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
	XMVECTOR posTmp = XMVectorZero(); // �S���[��
	posTmp = posTmp * speed_ * move;

	//�ړ��悪�t���A�������� (STAGE_OBJ::FLOOR => 0 ) �������炤����
	//if (map[ty][tx] == STAGE_OBJ::FLOOR)
	//{
	//	// posTmp.x , posTmp.z -> int tx,ty ; �z��̃C���f�b�N�X
		//pos = pos + speed_ * move;
	//}

	//Debug::Log("(X, Z)=");
	//Debug::Log(XMVectorGetX(pos));
	//Debug::Log(",");
	//Debug::Log(XMVectorGetZ(pos), true);
	int tx, ty;
	tx = (int)(XMVectorGetX(pos) + 0.5); // ( pos) �� (posTmp) �ɂ�����G���[ 
	ty = pStage_->GetStageWidth() / (int)(XMVectorGetZ(pos) + 0.5); // ��Ɠ���
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