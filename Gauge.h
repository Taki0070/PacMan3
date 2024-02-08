#pragma once
#include"Engine/GameObject.h"
class Gauge
	:public GameObject
{
	int hGaugeBar_;   //ゲージの画像
	int hGaugeFrame_;//フレーム画像
	
	int gaugeMaxVal_;//ゲージの最大
	int gaugeCrrVal_;//カレントの値(現在の値
 public:
	Gauge(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void SetGaugeVal(int _crr, int _max)
	{
		gaugeCrrVal_ = _crr;
		gaugeMaxVal_ = _max;

	}
};