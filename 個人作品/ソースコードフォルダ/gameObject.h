// GameObjectクラス [gameObject.h]
#pragma once

#include "renderer.h"

#include <list>
#include "component.h"
#include <chrono>

using namespace std::chrono;

class GameObject
{

protected:
	bool m_Destroy = false;

	DirectX::XMFLOAT3 m_Position = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	DirectX::XMFLOAT3 m_Rotation = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	DirectX::XMFLOAT3 m_Scale = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);

	DirectX::XMFLOAT2 m_LocalPos = DirectX::XMFLOAT2(0.0f, 0.0f);
	DirectX::XMFLOAT2 m_LocalSize = DirectX::XMFLOAT2(0.0f, 0.0f);
	DirectX::XMFLOAT2 m_LocalVelocity = DirectX::XMFLOAT2(0.0f, 0.0f);
	float m_Time = 0.0f;
	bool IsUI = false;
	
	float m_deltaTime;

	std::list<Component*> m_Component;
	std::list<GameObject*> m_ChildGameObject;

public:
	GameObject() {}
	virtual ~GameObject() {}


	DirectX::XMFLOAT3 GetPosition() { return m_Position; }
	DirectX::XMFLOAT3 GetRotation() { return m_Rotation; }
	DirectX::XMFLOAT3 GetScale() { return m_Scale; }
	void SetPosition(DirectX::XMFLOAT3 Position) { m_Position = Position; }
	void SetRotation(DirectX::XMFLOAT3 Rotation) { m_Rotation = Rotation; }
	void SetScale(DirectX::XMFLOAT3 Scale) { m_Scale = Scale; }
	void SetLocalPos(DirectX::XMFLOAT2 localpos) { m_LocalPos = localpos; }
	void SetLocalSize(DirectX::XMFLOAT2 localsize) { m_LocalSize = localsize; }
	void SetLocalVelocity(DirectX::XMFLOAT2 localvelocity) { m_LocalVelocity = localvelocity; }
	void SetUIFlag() { IsUI = true; }

	DirectX::XMFLOAT2* GetLocalPos() { return &m_LocalPos; }
	DirectX::XMFLOAT2* GetLocalSize() { return &m_LocalSize; }
	DirectX::XMFLOAT2* GetLocalVelocity() { return &m_LocalVelocity; }

	DirectX::XMFLOAT3 GetForward()//前方向ベクトル取得
	{
		DirectX::XMFLOAT4X4 rot;
		DirectX::XMStoreFloat4x4(&rot,
			DirectX::XMMatrixRotationRollPitchYaw(
				m_Rotation.x, m_Rotation.y, m_Rotation.z));

		DirectX::XMFLOAT3 forward;
		forward.x = rot._31;
		forward.y = rot._32;
		forward.z = rot._33;

		return forward;
	}

	void SetDestroy() { m_Destroy = true; }

	bool Destroy()
	{
		if (m_Destroy)
		{
			UninitBase();
			delete this;
			return true;
		}
		return false;
	}

	virtual void Init() {
		m_previousTime = high_resolution_clock::now();
	}
	virtual void Uninit() {}
	virtual void Update() {
		high_resolution_clock::time_point currentTime = high_resolution_clock::now();
		duration<float> timeSpan = duration_cast<duration<float>>(currentTime - m_previousTime);
		m_previousTime = currentTime;
		m_deltaTime = timeSpan.count();
	}
	virtual void Draw() {}
	virtual void PreDraw() {}





	template <typename T>
	T* AddComponent()
	{
		T* component = new T(this);
		m_Component.push_back(component);
		((Component*)component)->Init();

		return component;
	}


	template <typename T>
	T* GetComponent()
	{
		for (Component* component : m_Component)
		{
			if (typeid(*component) == typeid(T))
			{
				return (T*)component;
			}
		}
		return nullptr;
	}


	template <typename T>
	T* AddChild()
	{
		T* child = new T();
		m_ChildGameObject.push_back(child);
		child->InitBase();

		return child;
	}


	void InitBase()
	{
		Init();
	}


	void UninitBase()
	{
		Uninit();

		for (Component* component : m_Component)
		{
			component->Uninit();
			delete component;
		}
		m_Component.clear();
	}

	void UpdateBase()
	{

		for (Component* component : m_Component)
		{
			component->Update();
		}

		Update();
	}

	void DrawBase(DirectX::XMFLOAT4X4 ParentMatrix)
	{
		PreDraw();
		// マトリクス設定
		DirectX::XMFLOAT4X4 world;
		DirectX::XMMATRIX scale, rot, trans;
		scale = DirectX::XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
		rot = DirectX::XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
		trans = DirectX::XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
		DirectX::XMStoreFloat4x4(&world, scale * rot * trans
			* DirectX::XMLoadFloat4x4(&ParentMatrix));

		for (GameObject* child : m_ChildGameObject)
		{
			if (child == nullptr)
				break;
			child->DrawBase(world);
		}

		Renderer::SetWorldMatrix(&world);

		for (Component* component : m_Component)
		{
			component->Draw();
		}

		Draw();
	}

	private:
		high_resolution_clock::time_point m_previousTime;

};
