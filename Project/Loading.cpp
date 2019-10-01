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
	g_pResouseManager->Load();
	g_pResouseManager->AddTexture("sumple_imvisible.png", TEXTURE_FONT);
	g_pSoundManager->Load();
}

void CLoading::Initialize(void)
{
	g_pEffectManager->Initialize();
	g_pSoundManager->Initialize();
	g_pTimeManager->Reset();
}

void CLoading::Run(void) 
{
	Load();
	Initialize();

	m_bEnd = true;
}
