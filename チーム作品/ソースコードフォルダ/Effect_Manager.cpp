#include "Effect_Manager.h"
#include <Effekseer.h>//インクルードディレクトリを変更した後これを書く
#include <EffekseerRendererDX11.h>
#include "DirectX.h"

#define Angle_Radion(Angle) (Angle * 3.1415f / 180.0f)

//実体づくり
Effekseer::ManagerRef Effect_Manager::m_efkManager;
EffekseerRendererDX11::RendererRef Effect_Manager::m_efkRenderer;
std::map<std::string, Effect_Manager::Effect_Info> Effect_Manager::m_Effect;
std::list<Effect_Manager::Effect_Handle> Effect_Manager::m_HandleList;

void Effect_Manager::Effect_Init()
{
	//EffeckSeerの初期化
	m_efkManager = Effekseer::Manager::Create(1000);

	auto graphicsDevice =
		EffekseerRendererDX11::CreateGraphicsDevice(
			GetDevice(), GetContext());

	m_efkRenderer = EffekseerRendererDX11::Renderer::Create(graphicsDevice, 8000);

	m_efkManager->SetSpriteRenderer(m_efkRenderer->CreateSpriteRenderer());
	m_efkManager->SetRibbonRenderer(m_efkRenderer->CreateRibbonRenderer());
	m_efkManager->SetRingRenderer(m_efkRenderer->CreateRingRenderer());
	m_efkManager->SetTrackRenderer(m_efkRenderer->CreateTrackRenderer());
	m_efkManager->SetModelRenderer(m_efkRenderer->CreateModelRenderer());

	m_efkManager->SetTextureLoader(m_efkRenderer->CreateTextureLoader());
	m_efkManager->SetModelLoader(m_efkRenderer->CreateModelLoader());
	m_efkManager->SetMaterialLoader(m_efkRenderer->CreateMaterialLoader());
	m_efkManager->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());

	// ブロック
	Effect_Manager::Add_Effect("Gass", u"Assets/gass/gas.efkefc");
	Effect_Manager::Add_Effect("Stone", u"Assets/Effect/stone/Break_Stone.efkefc");
	Effect_Manager::Add_Effect("Clay", u"Assets/Effect/clay/Break_Clay.efkefc");
	Effect_Manager::Add_Effect("Concrete", u"Assets/Effect/concrete/Break_Concrete.efkefc");
	Effect_Manager::Add_Effect("Ice", u"Assets/Effect/ice/Break_Ice.efkefc");
	Effect_Manager::Add_Effect("IceFog", u"Assets/Effect/Ice_Effect/Ice.efkefc");
	Effect_Manager::Add_Effect("Soil", u"Assets/Effect/soil/Break_Soil.efkefc");
	Effect_Manager::Add_Effect("FallWater", u"Assets/Effect/Water_Effect/Water_Oti.efkefc");
	Effect_Manager::Add_Effect("Soak", u"Assets/Effect/Water_Effect/Water_Soak.efkefc");
	Effect_Manager::Add_Effect("HitEffect", u"Assets/Effect/HitEffect/HitEffect.efkefc");
	Effect_Manager::Add_Effect("WaterMove", u"Assets/Effect/water/WaterMove.efkefc");
	Effect_Manager::Add_Effect("WaterSprash", u"Assets/Effect/Sprash/Water_Sprash.efkefc");
	Effect_Manager::Add_Effect("Magma", u"Assets/Effect/magma/magma.efkefc");
	Effect_Manager::Add_Effect("MagmaMove", u"Assets/Effect/magma/MoveMagma.efkefc");
	Effect_Manager::Add_Effect("HitSand", u"Assets/Effect/Sand_Hit/Sand_Hit.efkefc");
	Effect_Manager::Add_Effect("SandSpread", u"Assets/Effect/sand/SandSpread.efkefc");

	// アイテム
	Effect_Manager::Add_Effect("Kirakira", u"Assets/Effect/item/kirakira.efkefc");
	Effect_Manager::Add_Effect("JewelyBreak", u"Assets/Effect/item/JewelyBreak.efkefc");
	Effect_Manager::Add_Effect("HeatBreak", u"Assets/Effect/item/HeatBreak.efkefc");

	// プレイヤー
	Effect_Manager::Add_Effect("Move", u"Assets/Effect/Move/Movement＿SP.efkefc");
	Effect_Manager::Add_Effect("Heat", u"Assets/Effect/item/Get_Heat.efkefc");
	Effect_Manager::Add_Effect("Item", u"Assets/Effect/item/Get_Item.efkefc");
	Effect_Manager::Add_Effect("Steam", u"Assets/Effect/Player/SteamEffect.efkefc");

	// チャージ
	Effect_Manager::Add_Effect("NormalCharge", u"Assets/Effect/charge/NormalCharge.efkefc");
	Effect_Manager::Add_Effect("HeatCharge", u"Assets/Effect/charge/HeatCharge.efkefc");

	// イベント
	Effect_Manager::Add_Effect("GameOver", u"Assets/Effect/EventEffect/GameOver.efkefc");
	Effect_Manager::Add_Effect("GameClear", u"Assets/Effect/ClearEffect/ClearEffect.efkefc");
	Effect_Manager::Add_Effect("Himei", u"Assets/Effect/Himei/Himei.efkefc");

	// 爆発
	Effect_Manager::Add_Effect("Explosion", u"Assets/Effect/Explosion/Explosion.efkefc");

}
void Effect_Manager::Effect_Uninit()
{
	//EffeckSeerの終了処理
	for (auto copy : m_Effect)
	{
		copy.second.effect.Reset();
	}
	m_Effect.clear();
	
	m_efkRenderer.Reset();
	m_efkManager.Reset();
	//-----------------------------------------
}

Effekseer::ManagerRef Effect_Manager::GetManager()
{
	return m_efkManager;
}

Effekseer::EffectRef Effect_Manager::GetEffect(std::string EffectName)
{
	return m_Effect[EffectName].effect;
}

void Effect_Manager::Add_Effect(std::string EffectName, const char16_t* FileName)
{
	std::map<std::string, Effect_Info>::iterator it = m_Effect.find(EffectName);

	//見つかった場合
	if (it != m_Effect.end()) {
		//MessageBox(nullptr, "もうその名前で作られています", "Error", MB_OK);
		return;
	}
	//追加
	m_Effect.insert(std::make_pair(EffectName, Effect_Info{}));

	Effekseer::ManagerRef n_efkManager;
	m_Effect[EffectName].effect = 
		Effekseer::Effect::Create(m_efkManager,FileName);
}

//エフェクトを再生する
void Effect_Manager::Play_Effect(std::string EffectName,DirectX::XMFLOAT3 Position,int DestroyCount)
{
	m_Effect[EffectName].Handle = m_efkManager->Play(m_Effect[EffectName].effect, Position.x, Position.y, -Position.z);
	
	Effect_Handle Temp = { m_Effect[EffectName].Handle ,0,DestroyCount };

	m_HandleList.push_back(Temp);
}

void Effect_Manager::Play_Effect(std::string EffectName, DirectX::XMFLOAT3 Position, DirectX::XMFLOAT3 Size, int DestroyCount)
{
	m_Effect[EffectName].Handle = m_efkManager->Play(m_Effect[EffectName].effect, Position.x, Position.y, -Position.z);
	m_efkManager->SetScale(m_Effect[EffectName].Handle, Size.x, Size.y, Size.z);

	Effect_Handle Temp = { m_Effect[EffectName].Handle ,0,DestroyCount};

	m_HandleList.push_back(Temp);
}

void Effect_Manager::Play_Effect(std::string EffectName, DirectX::XMFLOAT3 Position, DirectX::XMFLOAT3 Size, DirectX::XMFLOAT3 Angle, int DestroyCount)
{
	m_Effect[EffectName].Handle = m_efkManager->Play(m_Effect[EffectName].effect, Position.x, Position.y, -Position.z);
	m_efkManager->SetScale(m_Effect[EffectName].Handle, Size.x, Size.y, Size.z);
	m_efkManager->SetRotation(m_Effect[EffectName].Handle, Angle_Radion(Angle.x), Angle_Radion(Angle.y), Angle_Radion(Angle.z));

	Effect_Handle Temp = { m_Effect[EffectName].Handle ,0,DestroyCount };

	m_HandleList.push_back(Temp);
}

void Effect_Manager::All_EffectStop()
{
	for (auto it = m_HandleList.begin(); it != m_HandleList.end();)
	{
		//削除
		m_efkManager->StopEffect((*it).HANDLE);
		it = m_HandleList.erase(it);
	}
	m_HandleList.clear();
	m_efkManager->StopAllEffects();
}

void Effect_Manager::Stop_Effect(std::string EffectName)
{
	m_efkManager->StopEffect(m_Effect[EffectName].Handle);
}

//エフェクトを描画する
void Effect_Manager::Draw_Effect(CameraBase* pCamera)
{
	for(auto it = m_HandleList.begin(); it != m_HandleList.end();)
	{
		if((*it).DestroyCount < (*it).NowCount)
		{
			//削除
			m_efkManager->StopEffect((*it).HANDLE);
			it = m_HandleList.erase(it);
		}
		else
		{
			//カウントを増やす
			(*it).NowCount++;
			//次のエフェクトへ
			it++;
		}
	}


	//EffekSeer-------------------------------------------------------------------------
	const unsigned int SCREEN_WIDTH = 1280;
	const unsigned int SCREEN_HEIGHT = 720;

	static int Time = 0;

	DirectX::XMFLOAT3 Camera_Pos = pCamera->GetPos();
	DirectX::XMFLOAT3 Camera_Look = pCamera->GetLook();

	//---effekseerの描画

	//視点位置を設定
	auto viewrPosition = Effekseer::Vector3D(Camera_Pos.x,Camera_Pos.y, -Camera_Pos.z);
	auto lookPosition = Effekseer::Vector3D(Camera_Look.x, Camera_Look.y, -Camera_Look.z);

	//投影行列を設定(作成)
	Effekseer::Matrix44 projectMatrix;
	projectMatrix.PerspectiveFovRH(
		80.0f / 180.0f * 3.14f, (float)SCREEN_WIDTH / SCREEN_HEIGHT,
		1.0f, 500.0f);

	//カメラ行列を設定(作成)
	Effekseer::Matrix44 cameraMatrix;
	cameraMatrix.LookAtRH(viewrPosition,lookPosition,Effekseer::Vector3D(0.0f, 1.0f, 0.0f));

	//レイヤーパラメータの設定
	Effekseer::Manager::LayerParameter layerParameter;
	layerParameter.ViewerPosition = viewrPosition;
	m_efkManager->SetLayerParameter(0, layerParameter);

	//時間を更新する
	m_efkRenderer->SetTime(Time);

	//マネージャーの更新
	Effekseer::Manager::UpdateParameter updateParameter;
	m_efkManager->Update(updateParameter);

	//投影行列を設定
	m_efkRenderer->SetProjectionMatrix(projectMatrix);

	//カメラ行列を設定
	m_efkRenderer->SetCameraMatrix(cameraMatrix);
	//エフェクトの描画開始処理を行う
	m_efkRenderer->BeginRendering();

		//エフェクトの描画を行う
		Effekseer::Manager::DrawParameter drawParameter;
		drawParameter.ZNear = 0.0f;
		drawParameter.ZFar = 1.0f;
		drawParameter.ViewProjectionMatrix =
			m_efkRenderer->GetCameraProjectionMatrix();
		m_efkManager->Draw(drawParameter);

	//エフェクトの描画終了処理を行う
	m_efkRenderer->EndRendering();

	Time++;
}