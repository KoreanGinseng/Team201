//#pragma once
//
//
//#include		"GamePad.h"
//
//class CGameKey {
//private:
//	bool	m_bPush;
//	bool	m_bLastPush;
//	bool	m_bHold;
//
//	CGameKey(void) {
//
//		m_bPush = false;
//		m_bLastPush = false;
//		m_bHold = false;
//
//	};
//
//	~CGameKey(void) = default;
//	static CGameKey* m_pInstance;
//
//public:
//
//	bool	KeyUp(void);
//	bool	KeyDown(void);
//	bool	KeyLeft(void);
//	bool	KeyRigth(void);
//	bool	PushA(void);
//	bool	PushB(void);
//	bool	PushX(void);
//	bool	PushY(void);
//	bool	PushLB(void);
//	bool	PushRB(void);
//	bool	PushSTRAT(void);
//	bool	PushBACK(void);
//	bool	HoldLT(void);
//	bool	HoldRT(void);
//
//	void	RenderDebug(void);
//	void	Release(void);
//
//	static CGameKey* GetInstance(void) {
//
//		if (m_pInstance == nullptr) {
//
//			m_pInstance = NEW CGameKey();
//
//		}
//
//
//		return m_pInstance;
//
//	}
//
//
//};
//
//#define		g_pGameKey		CGameKey::GetInstance()
//
