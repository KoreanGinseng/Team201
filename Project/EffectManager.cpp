#include "EffectManager.h"



CEffectManager::CEffectManager(void)
{
}


CEffectManager::~CEffectManager(void)
{
}

CEffectManager * CEffectManager::GetEffect(void)
{
	static CEffectManager obj;
	return &obj;
}

CEffect * CEffectManager::GetEffect(const std::string & str)
{
	CEffect* re;
	int c = CEffectManager::GetEffect()->m_Resource[str].GetArrayCount();
	bool bFind = false;
	for (int i = 0; i < c; i++)
	{
		re = CEffectManager::GetEffect()->m_Resource[str].GetData(i);
		if (re->IsShow())
		{
			continue;
		}
		bFind = true;
		break;
	}
	if (!bFind)
	{
		CEffectManager::GetEffect()->m_Resource[str].Add(NEW CEffect());
		CEffectManager::GetEffect()->m_Resource[str].GetData(c)->Load(str.c_str());
		re = CEffectManager::GetEffect()->m_Resource[str].GetData(c);
	}
	return re;
}

void CEffectManager::Start(const std::string & str, const Vector2 & pos)
{
	CEffectManager::GetEffect(str)->Start(pos);
}

void CEffectManager::Start(const std::string & str, const float & x, const float & y)
{
	CEffectManager::Start(str, Vector2(x, y));
}

bool CEffectManager::Load(const std::string& str)
{
	for (int i = 0; i < DefEffectPool; i++)
	{
		CEffectManager::GetEffect()->m_Resource[str].Add(NEW CEffect());
		if (!CEffectManager::GetEffect()->m_Resource[str].GetData(i)->Load(str))
		{
			return false;
		}
	}
	return true;
}

void CEffectManager::Update(void)
{
	for (auto& itr : CEffectManager::GetEffect()->m_Resource)
	{
		int c = itr.second.GetArrayCount();
		for (int i = 0; i < c; i++)
		{
			itr.second.GetData(i)->Update();
		}
	}
}

void CEffectManager::Render(void)
{
	for (auto& itr : CEffectManager::GetEffect()->m_Resource)
	{
		int c = itr.second.GetArrayCount();
		for (int i = 0; i < c; i++)
		{
			itr.second.GetData(i)->Render();
		}
	}
}

void CEffectManager::Release(void)
{
	for (auto& itr : CEffectManager::GetEffect()->m_Resource)
	{
		int c = itr.second.GetArrayCount();
		for (int i = 0; i < c; i++)
		{
			itr.second.GetData(i)->Release();
			delete itr.second.GetData(i);
			itr.second.SetData(nullptr, i);
		}
		itr.second.Release();
	}
	CEffectManager::GetEffect()->m_Resource.clear();
}
