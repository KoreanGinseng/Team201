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
	g_pSoundManager->GetResource("");
	m_pScene->Load();
}

void CLoading::Initialize(void)
{
	g_pEffectManager->Initialize();
	g_pTimeManager->Reset();
	m_pScene->Initialize();
	Sleep(1000);
}

void CLoading::Run(void) 
{
	Load();
	Initialize();

	m_bEnd = true;
}
