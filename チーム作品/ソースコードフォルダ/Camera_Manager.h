//#pragma once
#ifndef H_CAMERA_MANAGER
#define H_CAMERA_MANAGER

#include "CameraBase.h"
#include "CameraEvent.h"
#include <DirectXMath.h>
#include "Position_struct.h"

class C_CameraManager
{
public:

	//ここにカメラの情報を作っていく
	enum SCENE_CAMERA_TYPE
	{
		_CAMERA_TITLE_FIRST = -1,
		_CAMERA_TITLE_END,
		
		_CAMERA_GAME_FIRST = -1,
		_CAMERA_GAME_ADMISSION,	//①　　入場カメラワーク
		_CAMERA_GAME_MAIN,		//②ー①ゲーム中のプレイヤーを見せる＋(Rスティックによる上下移動)
		_CAMERA_GAME_WORLD,		//②ー②全体を見せる(Rトリガーを押している間)
		_CAMERA_GAME_PILE,		//③ 　パイルバンカーについていく(打ち付けた時)
		_CAMERA_GAME_CLEAR,		//④ー①クリア後のダンス＋退場カメラワーク
		_CAMERA_GAME_MISS,		//④ー②ゲームオーバーのアニメーション用
		_CAMERA_GAME_STARTEVENT,
		
		_CAMERA_GAME_DEBUG,
		_CAMERA_GAME_END,
		_CAMERA_ALL_FIRST = 100,
		_CAMERA_ALL_EVENT,
		
	};

public:
	C_CameraManager(SCENE_CAMERA_TYPE NowType);	//継承した後でIndexを作る
	virtual ~C_CameraManager();
	void Update();
	void AddCamera(SCENE_CAMERA_TYPE AddType,CameraBase* AddCamera);
	CameraBase** Get_SceneCamera();					//カメラポインターのアドレスをもらう
	CameraBase* Get_NowCamera();					//今のカメラの情報をもらう
	SCENE_CAMERA_TYPE Get_NowType();					//今のカメラのタイプをもらう
	CameraBase* Get_TypeCamera(SCENE_CAMERA_TYPE Type);	//入れた型のカメラ情報をもらってくる
	void ChangeTypeCamera(SCENE_CAMERA_TYPE NextType);	//次のフレームで扱うカメラを指定
	void ChangeEventCamera(SCENE_CAMERA_TYPE NextType, DirectX::XMFLOAT3 startPos, DirectX::XMFLOAT3 endPos, float time);
	void ChangeCameraNew(SCENE_CAMERA_TYPE NextType, DirectX::XMFLOAT3 YetPos, DirectX::XMFLOAT3 YetLook);
	CameraBase** Get_CameraIndex();					//カメラをまとめた配列を持ってくる(とりあえず作ったけど多分使わん)
	DirectX::XMFLOAT2 ChangeScreenPos(FloatPos _3DPos);
	DirectX::XMFLOAT2 ChangeScreenPos(DirectX::XMFLOAT3 _3DPos);

protected:
	bool m_ChangeNow;				//カメラ情報が今のフレームで変えたか
	CameraBase* m_pSceneCamera;		//シーンのカメラの情報、この中を変えることでカメラを切り替える
	CameraBase** m_pCameraIndex;	//カメラの情報をまとめた変数、継承をした後に作る
	CameraEvent m_EventCamera;
	SCENE_CAMERA_TYPE m_NowType;		//今のカメラ
	SCENE_CAMERA_TYPE m_NextType;		//次のカメラ
};


#endif // !H_CAMERA_MANAGER
