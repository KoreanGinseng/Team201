#include "ResourceManager.h"

CResourceManager* CResourceManager::m_pInstance = nullptr;

bool CResourceManager::Load()
{
	return TRUE;
}

void CResourceManager::AddTexture(const TEXTUREDATA rt, const char* pName)
{
	CTexture tmp;
	tmp.Load(pName);
	m_TextureResource[rt] = tmp;
}

void CResourceManager::Release()
{

}