#include "AnimationManager.h"



CAnimationManager::CAnimationManager(void)
{
}


CAnimationManager::~CAnimationManager(void)
{
}

CAnimationManager * CAnimationManager::GetAnimation(void)
{
	static CAnimationManager obj;
	return &obj;
}

CAnimationData * CAnimationManager::GetAnimation(const std::string & str)
{
	if (CAnimationManager::GetAnimation()->m_Resource[str] == nullptr)
	{
		CAnimationManager::Load(str);
	}
	return CAnimationManager::GetAnimation()->m_Resource[str];
}

bool CAnimationManager::Load(const std::string& str)
{
	if (CAnimationManager::GetAnimation()->m_Resource[str] != nullptr)
	{
		return true;
	}
	CAnimationManager::GetAnimation()->m_Resource[str] = NEW CAnimationData();
	return CAnimationManager::GetAnimation(str)->Load(str.c_str());
}

void CAnimationManager::Release(void)
{
	for (auto& itr : CAnimationManager::GetAnimation()->m_Resource)
	{
		itr.second->Release();
		delete itr.second;
		itr.second = nullptr;
	}
	CAnimationManager::GetAnimation()->m_Resource.clear();
}
