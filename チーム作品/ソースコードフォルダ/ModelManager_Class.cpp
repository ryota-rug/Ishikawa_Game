#include "ModelManager_Class.h"
#include <Windows.h>
#include <DirectXMath.h>

#define GetRadion(Angle) (Angle * 3.141592f / 180.0f)

VertexShader* CModelManager::m_pVS_ModelManager;		//頂点シェーダー
ConstantBuffer* CModelManager::m_pWVP_ModelManager;	//定数バッファー

//連想配列
std::map < std::string,CModelManager::c_MODEL_INFORMATION> CModelManager::m_Model_Information;

CModelManager::CModelManager(CameraBase** Model_pCamera)
	:m_ppCamera(Model_pCamera)
{

}

CModelManager::~CModelManager()
{

}

//絶対呼ぶやつ!!
void CModelManager::c_ModelManager_Init()
{
	//シェーダー読み込み処理(前回作成したModelVS.csoを読み込む)
	m_pVS_ModelManager = new VertexShader;
	if (FAILED(m_pVS_ModelManager->Load("Assets/Shader/ModelVS.cso")))
	{
		MessageBox(nullptr, "ModelVS.cso", "Error", MB_OK);
	}

	//定数バッファ作成(ワールド、ビュー、プロジェクションのデータをシェーダに送る
	m_pWVP_ModelManager = new ConstantBuffer();
	m_pWVP_ModelManager->Create(sizeof(DirectX::XMFLOAT4X4) * 3);
}

void CModelManager::c_ModelManager_Uninit()
{
	for (auto& copy : m_Model_Information)
	{
		if (copy.second.model != nullptr)
		{
			copy.second.Animetion.clear();

			delete copy.second.model;
		}
	}
	m_Model_Information.clear();

	delete m_pWVP_ModelManager;
	delete m_pVS_ModelManager;
}

//モデルの情報を追加する
void CModelManager::c_AddModel(const std::string CharName, const char* FileName)
{
	//もうその中に実体がある場合
	std::map<std::string, c_MODEL_INFORMATION>::iterator it = m_Model_Information.find(CharName);

	//見つかった場合
	if (it != m_Model_Information.end()) {
		//MessageBox(nullptr, "もうその名前で作られています", CharName.c_str(), MB_OK);
		return;
	}

	//モデルの生成
	m_Model_Information.insert(std::make_pair(CharName,
		c_MODEL_INFORMATION{ nullptr }));

	//モデルをメモリに作る
	m_Model_Information[CharName].model = new Model;

	//シェーダーの設定
	m_Model_Information[CharName].model->SetVertexShader(m_pVS_ModelManager);

	//モデルのロード処理
	if (!m_Model_Information[CharName].model->Load(FileName, 1.0f, false))
	{
		//MessageBox(nullptr, "モデル読み込みエラー!", FileName, MB_OK);
	}

	m_Model_Information[CharName].AnimeNow = false;
}

void CModelManager::c_AddModel(const std::string CharName, const char* FileName, const char* TextureName)
{
	//もうその中に実体がある場合
	std::map<std::string, c_MODEL_INFORMATION>::iterator it = m_Model_Information.find(CharName);

	//見つかった場合
	if (it != m_Model_Information.end()) {
		//MessageBox(nullptr, "もうその名前で作られています", CharName.c_str(), MB_OK);
		return;
	}

	//モデルの生成
	m_Model_Information.insert(std::make_pair(CharName,
		c_MODEL_INFORMATION{ nullptr }));

	//モデルをメモリに作る
	m_Model_Information[CharName].model = new Model;

	//シェーダーの設定
	m_Model_Information[CharName].model->SetVertexShader(m_pVS_ModelManager);

	//モデルのロード処理
	if (!m_Model_Information[CharName].model->LoadAndTexture(FileName, TextureName, 1.0f, false))
	{
		//MessageBox(nullptr, "モデル読み込みエラー!", FileName, MB_OK);
	}

	m_Model_Information[CharName].AnimeNow = false;
}

void CModelManager::c_AddAnimetion(const std::string AnimeName, const char* AnimeFileName, const std::string CharName,float StartFrame)		//アニメーションを追加する
{
	std::map<std::string, c_MODEL_INFORMATION>::iterator ModelIt = m_Model_Information.find(CharName);
	//実体がなかった場合
	if (ModelIt == m_Model_Information.end()) {
		MessageBox(nullptr,"情報がないのでアニメーションを追加できません", CharName.c_str(), MB_OK);
		return;
	}
	//実体がない場合
	if(m_Model_Information[CharName].model == nullptr)
	{
		MessageBox(nullptr, "追加したいモデルの実態がないのでアニメーションを追加できません", CharName.c_str(), MB_OK);
		return;
	}

	//もうその中に実体がある場合
	std::map<std::string, Model::AnimeNo>::iterator animeIt = m_Model_Information[CharName].Animetion.find(AnimeName);

	//見つかった場合
	if (animeIt != m_Model_Information[CharName].Animetion.end()) {
		//MessageBox(nullptr, "もうその名前で作られています", CharName.c_str(), MB_OK);
		return;
	}

	m_Model_Information[CharName].Animetion.insert(std::make_pair(AnimeName,
		Model::AnimeNo{ m_Model_Information[CharName].model->AddAnimation(AnimeFileName,StartFrame) }));

	if (m_Model_Information[CharName].Animetion[AnimeName] == Model::ANIME_NONE)
	{
		MessageBox(nullptr, "アニメーションエラー", "Error", MB_OK);
		return;
	}
}

void CModelManager::c_SetAnimetion(const std::string CharName, const std::string AnimeName, bool Repeat)
{
	std::map<std::string, c_MODEL_INFORMATION>::iterator modelit = m_Model_Information.find(CharName);
	//実体がなかった場合
	if (modelit == m_Model_Information.end()) {
		MessageBox(nullptr, "その名前のモデルがないのでアニメーションを再生できません", CharName.c_str(), MB_OK);
		return;
	}
	//実体がない場合
	if (m_Model_Information[CharName].model == nullptr)
	{
		MessageBox(nullptr, "モデルの実態がないのでアニメーションを再生できません", CharName.c_str(), MB_OK);
		return;
	}
	//アニメーションが登録されているかの確認
	auto animeit = m_Model_Information[CharName].Animetion.find(AnimeName);
	if (animeit == m_Model_Information[CharName].Animetion.end())
	{
		MessageBox(nullptr, "そのアニメーションが登録されてないので再生できません", CharName.c_str(), MB_OK);
		return;
	}

	//アニメーションの再生
	m_Model_Information[CharName].model->Play(m_Model_Information[CharName].Animetion[AnimeName], Repeat);
	m_Model_Information[CharName].AnimeNow = true;
}

void CModelManager::c_AllDelete()			//全てのモデル情報を消す
{
	//for (std::pair<std::string, MODEL_INFORMATION> copy : Model_Information)
	for (auto& copy : m_Model_Information)
	{
		if (copy.second.model != nullptr)
		{
			delete copy.second.model;
		}
	}
	m_Model_Information.clear();
}

//何も変えずに描画する
void CModelManager::c_ModelDraw(const std::string Name)
{
	c_ModelDraw(Name, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f);
}

//モデルを引数の情報をもとに描画する
void CModelManager::c_ModelDraw(const std::string CharName, float PosX, float PosY, float PosZ, float ScaleX, float ScaleY, float ScaleZ, float AngleX, float AngleY, float AngleZ)
{
	ScaleX *= 1.32f;
	ScaleY *= 1.32f;
	ScaleZ *= 1.32f;
	std::map<std::string, c_MODEL_INFORMATION>::iterator it = m_Model_Information.find(CharName);
	//実体がなかった場合
	if (it == m_Model_Information.end()) {
		//MessageBox(nullptr,"モデルがないので描画できません", "Error", MB_OK);
		return;
	}

	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(PosX, PosY, PosZ);	//移動
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(ScaleX, ScaleY, ScaleZ);//拡大縮小行列
	
	//回転行列はやる場合とやらない場合があるため
	DirectX::XMMATRIX world;
	world = S;

	if (AngleX != 0.0f)
	{
		DirectX::XMMATRIX Rx = DirectX::XMMatrixRotationX(GetRadion(AngleX));//X回転行列
		world *= Rx;
	}

	if (AngleY != 0.0f)
	{
		DirectX::XMMATRIX Ry = DirectX::XMMatrixRotationY(GetRadion(AngleY));//X回転行列
		world *= Ry;
	}

	if (AngleZ != 0.0f)
	{
		DirectX::XMMATRIX Rz = DirectX::XMMatrixRotationZ(GetRadion(AngleZ));//X回転行列
		world *= Rz;
	}

	world *= T;
	
	DirectX::XMStoreFloat4x4(&mat[0],
	DirectX::XMMatrixTranspose(world));
	mat[1] = (*m_ppCamera)->GetViewMatrix();		//カメラの情報が分かり次第実装
	mat[2] = (*m_ppCamera)->GetProjectionMatrix();		//カメラの情報が分かり次第実装
	m_pWVP_ModelManager->Write(mat);
	m_pWVP_ModelManager->BindVS(0);
	
	if(m_Model_Information[CharName].AnimeNow)
	m_Model_Information[CharName].model->Step(1.0f / 60.0f);
	
	
	m_Model_Information[CharName].model->Draw();
}

void CModelManager::c_SetCamera(CameraBase* NewPointer)
{
	delete *m_ppCamera;

	*m_ppCamera = NewPointer;
}

CameraBase* CModelManager::c_GetCamera()
{
	return *m_ppCamera;
}
