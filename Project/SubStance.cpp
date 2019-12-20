#include	"Substance.h"

CSubstance::CSubstance(void) :
CCharacter()
{
	m_SubType = -1;
	m_SubStatus = SUBSTATUS_NOMAL;
	m_bTarget = false;
	m_bSelectTarget = true;
	m_bAnimStop = false;
}

void CSubstance::Stop(void)
{
	if (m_SubType == SUB_ENE)
	{
		m_SubStatus = SUBSTATUS_STOP;
		m_bAnimStop = true;
		m_WaitCount = 180;
		//g_pSoundManager->GetResource("")->Play();
	}
	else
	{
		//g_pSoundManager->GetResource("")->Play();
	}
}

void CSubstance::Back(void)
{
	if (m_SubType != SUB_ENE && m_SubStatus != SUBSTATUS_BACK)
	{
		if (m_SubStatus == SUBSTATUS_NOMAL)
		{
			m_SubStatus = SUBSTATUS_BACK;
			//g_pSoundManager->GetResource("")->Play();
		}
		else
		{
			m_SubStatus = SUBSTATUS_NOMAL;
			//g_pSoundManager->GetResource("")->Play();
		}
		m_Motion.ChangeMotion(m_SubStatus);
	}
}
void CSubstance::Trip(void)
{
	if (m_SubType != SUB_ENE && m_SubStatus != SUBSTATUS_TRIP)
	{
		if (m_SubStatus == SUBSTATUS_NOMAL)
		{
			m_SubStatus = SUBSTATUS_TRIP;
 			//g_pSoundManager->GetResource("")->Play();
		}
		else
		{
			m_SubStatus = SUBSTATUS_NOMAL;
			//g_pSoundManager->GetResource("")->Play();
		}
		m_Motion.ChangeMotion(m_SubStatus);
	}
}
