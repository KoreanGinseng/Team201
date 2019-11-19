#include "EffectFade.h"



CEffectFade::CEffectFade()
{
	m_pMaskTexture = g_pTextureManager->GetResource("MaskImage.png");
	m_bEnd = false;
}


CEffectFade::~CEffectFade()
{
}

bool CEffectFade::Out(const int & spd)
{
	if (!m_bStart[1])
	{
		m_Alpha = 0;
		m_Spd = spd;
		m_bStart[1] = true;
		m_bEnd = false;
	}
	m_Alpha += m_Spd;
	if (m_Alpha > 255)
	{
		m_bStart[1] = false;
		m_bEnd = true;
		return true;
	}
	return false;	
}

bool CEffectFade::In(const int & spd)
{
	if (!m_bStart[0])
	{
		m_Alpha = 255;
		m_Spd = spd;
		m_bStart[0] = true;
		m_bEnd = false;
	}
	m_Alpha -= m_Spd;
	if (m_Alpha < 0) {
		m_bStart[0] = false;
		//m_bEnd = true;
		return true;
	}
	return false;
}

bool CEffectFade::Render(void)
{
	if (!IsStart())
	{
		return true;
	}
	if (m_pMaskTexture == nullptr)
	{
		return false;
	}
	return m_pMaskTexture->Render(0, 0, MOF_ARGB(m_Alpha, 255, 255, 255));
}
