#include "Loading.h"



CLoading::CLoading() :
m_bEnd(false)
{
}


CLoading::~CLoading()
{
}

void CLoading::Load(void)
{
	g_pEffectManager->Load();
	for (int i = TEXTURE_PLAYER; i < TEXTURE_COUNT; i++)
	{
		g_pTextureManager->GetResource(FileName[i]);
	}
	for (int i = ANIMATION_PLAYER; i < ANIMATION_COUNT; i++)
	{
		g_pAnimManager->GetResource(FileName[i]);
	}
	for (int i = SOUND_JUMP; i < SOUND_COUNT; i++)
	{
		g_pSoundManager->GetResource(FileName[i]);
	}
	m_pScene->Load();
}

void CLoading::Initialize(void)
{
	g_pEffectManager->Initialize();
	m_pScene->Initialize();
	//Sleep(1000);
}

void CLoading::Run(void) 
{
	Load();
	Initialize();

	m_bEnd = true;
}
