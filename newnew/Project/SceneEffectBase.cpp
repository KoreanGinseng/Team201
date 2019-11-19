#include "SceneEffectBase.h"



CSceneEffectBase::CSceneEffectBase()
{
	m_bStart[0] = false;
	m_bStart[1] = false;
	m_bEnd = false;
}


CSceneEffectBase::~CSceneEffectBase()
{
}

bool CSceneEffectBase::Frame(void)
{
	if (m_bStart[0])
	{
		In(m_Spd);
	}
	else if (m_bStart[1])
	{
		Out(m_Spd);
	}
	return true;
}
