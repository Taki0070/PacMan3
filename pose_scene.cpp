#include "pose_scene.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

pose_scene::pose_scene(GameObject* parent)
	:GameObject(parent, "TITLE_SCENE"), hPict_(-1)
{

}

void pose_scene::Initialize()
{
	hPict_ = Image::Load("Image\\pose.png");
	assert(hPict_ >= 0);
}
//ok
void pose_scene::Update()
{
	if (Input::IsKey(DIK_O))
	{
		SceneManager* pS = (SceneManager*)FindObject("SceneManager");
		pS->ChangeScene(SCENE_ID_PLAY);
	}


}

void pose_scene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

void pose_scene::Release()
{
}
