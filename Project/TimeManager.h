#pragma once
#include	"Mof.h"

class CTimeManager {
private:
	float	m_Time;

	static CTimeManager*	m_pInstance;
	CTimeManager() = default;
	~CTimeManager() = default;
public:
	void Tick(void) { m_Time += CUtilities::GetFrameSecond(); }
	void Reset(void) { m_Time = 0; }
	float GetNowTime(void) { return m_Time; }
	static CTimeManager* GetInsctance(void) {
		if (m_pInstance == nullptr) {
			m_pInstance = new CTimeManager();
		}
		return m_pInstance;
	}
};

#define		g_pTimeManager	CTimeManager::GetInsctance()