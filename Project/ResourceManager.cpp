#include "ResourceManager.h"



CResourceManager::CResourceManager()
{
}


CResourceManager::~CResourceManager()
{
	delete m_Instance;
}

bool CResourceManager::Load()
{
	for (int i = 0; i < TEXTURE_COUNT; ++i)
	{
		m_TextureResource.at((TEXTUREDATA)i).Load(m_TextureName[i]);
	}


	return TRUE;
}