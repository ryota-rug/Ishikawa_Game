//#pragma once
#ifndef EFFECT_MANAGER_H
#define EFFECT_MANAGER_H
#include <Effekseer.h>
#include <EffekseerRendererDX11.h>
#include <map>
#include <string>
#include "CameraBase.h"
#include <DirectXMath.h>
#include <list>

class Effect_Manager
{
public:
	typedef struct 
	{
		Effekseer::EffectRef effect;
		Effekseer::Handle Handle;
		float time;
	}Effect_Info;

	typedef struct
	{
		Effekseer::Handle HANDLE;
		int NowCount;
		int DestroyCount;
	}Effect_Handle;

public:
	static void Effect_Init();
	static void Effect_Uninit();
	static Effekseer::ManagerRef GetManager();
	static Effekseer::EffectRef GetEffect(std::string EffectName);
	static void Add_Effect(std::string EffectName, const char16_t* FileName);	//エフェクト情報の追加
	static void Play_Effect(std::string EffectName, DirectX::XMFLOAT3 Position, int DestroyCount = 100);	//エフェクトを再生
	static void Play_Effect(std::string EffectName,DirectX::XMFLOAT3 Position, DirectX::XMFLOAT3 Size,int DestroyCount = 100);	//エフェクトを再生
	static void Play_Effect(std::string EffectName,DirectX::XMFLOAT3 Position, DirectX::XMFLOAT3 Size,DirectX::XMFLOAT3 Angle,int DestroyCount = 100);	//エフェクトを再生
	static void All_EffectStop();
	static void Stop_Effect(std::string EffectName);
	static void Draw_Effect(CameraBase* pCamera);	//エフェクトを描画

private:
	static Effekseer::ManagerRef m_efkManager;
	static EffekseerRendererDX11::RendererRef m_efkRenderer;
	static std::map<std::string, Effect_Manager::Effect_Info> m_Effect;
	static std::list<Effect_Manager::Effect_Handle> m_HandleList;
};


#endif // !EFFECT_MANAGER_H
