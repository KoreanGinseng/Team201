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
}

void CLoading::Initialize(void)
{

}

void CLoading::Run(void) 
{



	m_bEnd = true;
}