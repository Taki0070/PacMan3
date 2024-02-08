#pragma once
#include "Engine/GameObject.h"
class Stage;//�|�C���^

class Player :
	public GameObject
{
	int hModel_;
	float speed_;
	Stage* pStage_;
	int hpMax_;//�ő�Hp
	int hpCrr_;//�gP
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Player(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

