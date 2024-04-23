#ifndef ___GAMECAMERA_H___
#define ___GAMECAMERA_H___

#include <DirectXMath.h>

//—ñ‹“Œ^
enum CameraKind
{
	CAM_DEBUG,
	CAM_EVENT,
	MAX_CAMERA //ƒJƒƒ‰Å‘å”
};


void InitGameCamera();
void UninitGameCamera();
void UpdateGameCamera();
void DrawGameCamera();

DirectX::XMFLOAT4X4 Get_ProtMat();
DirectX::XMFLOAT4X4 Get_ViewMat();


#endif // !___GAMECAMERA_H___
