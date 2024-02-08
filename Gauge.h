#pragma once
#include"Engine/GameObject.h"
class Gauge
	:public GameObject
{
	int hGaugeBar_;   //�Q�[�W�̉摜
	int hGaugeFrame_;//�t���[���摜
	
	int gaugeMaxVal_;//�Q�[�W�̍ő�
	int gaugeCrrVal_;//�J�����g�̒l(���݂̒l
 public:
	Gauge(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void SetGaugeVal(int _crr, int _max)
	{
		gaugeCrrVal_ = _crr;
		gaugeMaxVal_ = _max;

	}
};