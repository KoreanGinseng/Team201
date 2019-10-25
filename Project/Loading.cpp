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
	auto c = CUtilities::GetCurrentDirectory();
	CTexture a;
	a.Load("player3.png");
	int b = a.GetHeight();
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
	g_pTimeManager->Reset();
	m_pScene->Initialize();
	//Sleep(1000);
}

void CLoading::Run(void) 
{
	m_bEnd = false;
	MOF_PRINTLOG("thred Start\n");
	Load();
	Initialize();

	m_bEnd = true;
	MOF_PRINTLOG("thred End\n");
}
