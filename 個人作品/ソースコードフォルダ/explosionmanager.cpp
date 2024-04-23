#include "explosionmanager.h"
#include "explosion.h"
#include "bomb.h"
#include "manager.h"
#include "game.h"
#include "audio.h"


void ExplosionManager::Init()
{
	m_SE = AddComponent<Audio>();
	m_SE->Load("asset/audio/explosion2.wav");
}

void ExplosionManager::Generate(FieldManager::Info* info)
{
	Game* scene = static_cast<Game*>(Manager::GetScene());
	FieldManager* field_man = scene->GetFieldMan();
	int X = info->numX;
	int Y = info->numY;
	int power = info->bomb->GetPower();
	FieldManager::Info* adjance_info;
	Explosion* explosion;


	m_SE->Play();

	explosion = scene->AddGameObject<Explosion>();
	explosion->SetPosition(DirectX::XMFLOAT3(info->point.x, info->point.y + 1.0f, info->point.z));
	explosion->SetScale(DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));
	explosion->SetInfo(info);

	// âE
	for (int i = 1; i <= power; i++)
	{
		adjance_info = field_man->GetInfo(X + i, Y);
		if (adjance_info->explosion == true)
		{
			explosion = scene->AddGameObject<Explosion>();
			explosion->SetPosition(DirectX::XMFLOAT3(adjance_info->point.x,adjance_info->point.y+1.0f,adjance_info->point.z));
			explosion->SetScale(DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));
			explosion->SetInfo(adjance_info);
		}
		else
		{
			break;
		}
	}
	// ç∂
	for (int i = -1; i >= -power; i--)
	{
		adjance_info = field_man->GetInfo(X + i, Y);
		if (adjance_info->explosion == true)
		{
			explosion = scene->AddGameObject<Explosion>();
			explosion->SetPosition(DirectX::XMFLOAT3(adjance_info->point.x, adjance_info->point.y + 1.0f, adjance_info->point.z));
			explosion->SetScale(DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));
			explosion->SetInfo(adjance_info);
		}
		else
		{
			break;
		}
	}
	// è„
	for (int j = 1; j <= power; j++)
	{
		adjance_info = field_man->GetInfo(X, Y + j);
		if (adjance_info->explosion == true)
		{
			explosion = scene->AddGameObject<Explosion>();
			explosion->SetPosition(DirectX::XMFLOAT3(adjance_info->point.x, adjance_info->point.y + 1.0f, adjance_info->point.z));
			explosion->SetScale(DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));
			explosion->SetInfo(adjance_info);
		}
		else
		{
			break;
		}
	}
	// â∫
	for (int j = -1; j >= -power; j--)
	{
		adjance_info = field_man->GetInfo(X, Y + j);
		if (adjance_info->explosion == true)
		{
			explosion = scene->AddGameObject<Explosion>();
			explosion->SetPosition(DirectX::XMFLOAT3(adjance_info->point.x, adjance_info->point.y + 1.0f, adjance_info->point.z));
			explosion->SetScale(DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));
			explosion->SetInfo(adjance_info);
		}
		else
		{
			break;
		}
	}
}
