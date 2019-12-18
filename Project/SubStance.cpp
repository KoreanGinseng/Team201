#include	"Substance.h"

void CSubstance::Stop(void)
{
	if (m_SubType == SUB_ENE)
	{
		g_pSoundManager->GetResource("")->Play();
	}
	else
	{
		g_pSoundManager->GetResource("")->Play();
	}
}

void CSubstance::Back(void)
{
	if (m_SubType != SUB_ENE && m_SubStatus != SUBSTATUS_BACK)
	{
		if (m_SubStatus == SUBSTATUS_NOMAL)
		{
			m_SubStatus = SUBSTATUS_BACK;
			g_pSoundManager->GetResource("")->Play();
		}
		else
		{
			m_SubStatus = SUBSTATUS_NOMAL;
			g_pSoundManager->GetResource("")->Play();
		}
	}
}
void CSubstance::Trip(void)
{
	if (m_SubType != SUB_ENE && m_SubStatus != SUBSTATUS_TRIP)
	{
		if (m_SubStatus == SUBSTATUS_NOMAL)
		{
			m_SubStatus = SUBSTATUS_TRIP;
			g_pSoundManager->GetResource("")->Play();
		}
		else
		{
			m_SubStatus = SUBSTATUS_NOMAL;
			g_pSoundManager->GetResource("")->Play();
		}
	}
}