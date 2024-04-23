#include "ModelManager.h"
#include "GameCamera.h"

#define GetRadion(Angle) (Angle * 3.141592f / 180.0f)

//構造体
typedef struct
{
	Model *model;			//モデル情報を入れておく変数
}MODEL_INFORMATION;

VertexShader* pVS_ModelManager;		//頂点シェーダー
ConstantBuffer* pWVP_ModelManager;	//定数バッファー

//連想配列
std::map < std::string, MODEL_INFORMATION> Model_Information;

//絶対呼ぶやつ!!
void ModelManager_Init()
{
	//シェーダー読み込み処理(前回作成したModelVS.csoを読み込む)
	pVS_ModelManager = new VertexShader;
	if (FAILED(pVS_ModelManager->Load("Assets/Shader/ModelVS.cso")))
	{
		MessageBox(nullptr, "ModelVS.cso", "Error", MB_OK);
	}

	//定数バッファ作成(ワールド、ビュー、プロジェクションのデータをシェーダに送る
	pWVP_ModelManager = new ConstantBuffer();
	pWVP_ModelManager->Create(sizeof(DirectX::XMFLOAT4X4) * 3);
}

void ModelManager_Uninit()
{
	for (auto& copy : Model_Information)
	{
		if (copy.second.model != nullptr)
		{
			delete copy.second.model;
		}
	}
	Model_Information.clear();

	delete pWVP_ModelManager;
	delete pVS_ModelManager;
}

//モデルの情報を追加する
void AddModel(const std::string CharName,const char* FileName)
{
	static int Count = 0;
	Count++;
	//もうその中に実体がある場合
	std::map<std::string, MODEL_INFORMATION>::iterator it = Model_Information.find(CharName);
	
	//見つかった場合
	if (it != Model_Information.end()){
		//MessageBox(nullptr, "もうその名前で作られています", "Error", MB_OK);
		return;
	}

	//モデルの生成
	Model_Information.insert(std::make_pair(CharName, 
		MODEL_INFORMATION{ nullptr }));

	//モデルをメモリに作る
	Model_Information[CharName].model = new Model;

	//シェーダーの設定
	Model_Information[CharName].model->SetVertexShader(pVS_ModelManager);

	//モデルのロード処理
	if (!Model_Information[CharName].model->Load(FileName, 1.0f, false))
	{
		MessageBox(nullptr, "モデルエラー!!!!!", "Error", MB_OK);
	}
}

void AllDelete()			//全てのモデル情報を消す
{
	//for (std::pair<std::string, MODEL_INFORMATION> copy : Model_Information)
	for (auto& copy : Model_Information)
	{
		if (copy.second.model != nullptr)
		{
			delete copy.second.model;
		}
	}
	Model_Information.clear();
}

//何も変えずに描画する
void ModelDraw(const std::string Name)
{
	ModelDraw(Name, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f);
}

//モデルを引数の情報をもとに描画する
void ModelDraw(const std::string CharName, float PosX, float PosY, float PosZ, float ScaleX, float ScaleY, float ScaleZ, float AngleX, float AngleY, float AngleZ)
{
	std::map<std::string, MODEL_INFORMATION>::iterator it = Model_Information.find(CharName);
	//実体がなかった場合
	if (it == Model_Information.end()) {
		MessageBox(nullptr, "モデルエラー", "Error", MB_OK);
		return;
	}

	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(PosX, PosY, PosZ);	//移動
	DirectX::XMMATRIX Rx = DirectX::XMMatrixRotationX(GetRadion(AngleX));//X回転行列
	DirectX::XMMATRIX Ry = DirectX::XMMatrixRotationY(GetRadion(AngleY));//Y回転行列
	DirectX::XMMATRIX Rz = DirectX::XMMatrixRotationZ(GetRadion(AngleZ));//Z回転行列
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(ScaleX, ScaleY, ScaleZ);//拡大縮小行列
	DirectX::XMMATRIX world = S * Rx * Ry * Rz * T;//ワールド座標系行列の作成
	DirectX::XMStoreFloat4x4(&mat[0],
		DirectX::XMMatrixTranspose(world));
	mat[1] = Get_ViewMat();		//カメラの情報が分かり次第実装
	mat[2] = Get_ProtMat();		//カメラの情報が分かり次第実装
	pWVP_ModelManager->Write(mat);
	pWVP_ModelManager->BindVS(0);

	Model_Information[CharName].model->Draw();
}
