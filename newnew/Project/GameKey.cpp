//#include		"GameKey.h"
//
//CGameKey* CGameKey::m_pInstance = nullptr;
//
//bool CGameKey::KeyUp() {
//
//	long Pov = g_pGamePad->GetPadState()->rgdwPOV[0];
//
//	//前回押してたが放した場合
//	if (m_bLastPush&&Pov == -1) {
//
//		//押せるようになる
//		m_bLastPush = false;
//
//
//	}
//	else if (m_bLastPush) {
//
//		return false;
//
//	}
//
//
//
//	//放していて上キーを押した場合
//	if (Pov == 0 && !m_bLastPush) {
//
//		/*m_bPush = true;*/
//		m_bLastPush = true;
//
//	}
//
//
//
//
//	return m_bLastPush;
//
//}
//
//bool CGameKey::KeyDown() {
//
//	long Pov = g_pGamePad->GetPadState()->rgdwPOV[0];
//
//	//前回押してたが放した場合
//	if (m_bLastPush&&Pov == -1) {
//
//		//押せるようになる
//		m_bLastPush = false;
//
//
//	}
//	else if (m_bLastPush) {
//
//		return false;
//
//	}
//
//
//
//	//放していて上キーを押した場合
//	if (Pov / 100 == 180 && !m_bLastPush) {
//
//		/*m_bPush = true;*/
//		m_bLastPush = true;
//
//	}
//
//
//
//
//	return m_bLastPush;
//
//}
//
//bool CGameKey::KeyLeft() {
//
//	long Pov = g_pGamePad->GetPadState()->rgdwPOV[0];
//
//	//前回押してたが放した場合
//	if (m_bLastPush&&Pov == -1) {
//
//		//押せるようになる
//		m_bLastPush = false;
//
//
//	}
//	else if (m_bLastPush) {
//
//		return false;
//
//	}
//
//
//
//	//放していて上キーを押した場合
//	if (Pov / 100 == 270 && !m_bLastPush) {
//
//		/*m_bPush = true;*/
//		m_bLastPush = true;
//
//	}
//
//
//
//
//	return m_bLastPush;
//
//
//}
//
//bool CGameKey::KeyRigth() {
//
//	long Pov = g_pGamePad->GetPadState()->rgdwPOV[0];
//
//	//前回押してたが放した場合
//	if (m_bLastPush&&Pov == -1) {
//
//		//押せるようになる
//		m_bLastPush = false;
//
//
//	}
//	else if (m_bLastPush) {
//
//		return false;
//
//	}
//
//
//
//	//放していて上キーを押した場合
//	if (Pov / 100 == 90 && !m_bLastPush) {
//
//		/*m_bPush = true;*/
//		m_bLastPush = true;
//
//	}
//
//
//
//
//	return m_bLastPush;
//
//
//}
//
//void CGameKey::RenderDebug() {
//
//	CGraphicsUtilities::RenderString(0, 0, "Push %d LastPush %d", m_bPush, m_bLastPush);
//
//	long Pov = g_pGamePad->GetPadState()->rgdwPOV[0];
//
//	CGraphicsUtilities::RenderString(0, 30, "%ld", Pov);
//	CGraphicsUtilities::RenderString(0, 60, "%ld", Pov / 100);
//}
//
//bool CGameKey::PushA() {
//
//	return g_pGamePad->IsKeyPush(GAMEKEY_A);
//
//}
//
//bool CGameKey::PushB() {
//
//	return g_pGamePad->IsKeyPush(GAMEKEY_B);
//
//}
//
//bool CGameKey::PushX() {
//
//	return g_pGamePad->IsKeyPush(GAMEKEY_X);
//
//}
//
//bool CGameKey::PushY() {
//
//	return g_pGamePad->IsKeyPush(GAMEKEY_Y);
//
//}
//
//bool CGameKey::PushLB() {
//
//	return g_pGamePad->IsKeyPush(GAMEKEY_LB);
//
//}
//
//bool CGameKey::PushRB() {
//
//	return g_pGamePad->IsKeyPush(GAMEKEY_RB);
//
//}
//
//bool CGameKey::PushSTRAT() {
//
//	return g_pGamePad->IsKeyPush(GAMEKEY_START);
//
//}
//
//bool CGameKey::PushBACK() {
//
//	return g_pGamePad->IsKeyPush(GAMEKEY_BACK);
//
//}
//
//bool CGameKey::HoldLT() {
//
//
//
//	if (g_pGamePad->GetPadState()->lZ >= 500.0f) {
//
//		m_bHold = true;
//
//	}
//	else {
//
//		m_bHold = false;
//
//	}
//
//	return m_bHold;
//
//}
//
//bool CGameKey::HoldRT() {
//
//	if (g_pGamePad->GetPadState()->lZ <= -500.0f) {
//
//		m_bHold = true;
//
//	}
//	else {
//
//		m_bHold = false;
//
//	}
//
//	return m_bHold;
//
//}
//void CGameKey::Release() {
//
//	//自身の解放
//	if (m_pInstance) {
//
//		delete m_pInstance;
//
//		m_pInstance = nullptr;
//
//	}
//
//}
//
