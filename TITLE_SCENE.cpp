#include "TITLE_SCENE.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

TITLE_SCENE::TITLE_SCENE(GameObject* parent)
	:GameObject(parent, "TITLE_SCENE"), hPict_(-1)
{

}

void TITLE_SCENE::Initialize()
{
	hPict_ = Image::Load("Image\\table.png");
	assert(hPict_ >= 0);
}
//ok
void TITLE_SCENE::Update()
{
	if (Input::IsKey(DIK_SPACE))
	{
		SceneManager* pS = (SceneManager*)FindObject("SceneManager");
		pS->ChangeScene(SCENE_ID_PLAY);
	}
}

void TITLE_SCENE::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

void TITLE_SCENE::Release()
{
}
