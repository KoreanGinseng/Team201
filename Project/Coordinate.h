#pragma once
#include	"Mof.h"
#include	"GameDefine.h"
#include	"Camera2D.h"

//関数のプロトタイプ宣言
Vector2 WorldTransration(Vector2 cp, Vector2 sp);
Vector2 ScreenTransration(Vector2 cp, Vector2 wp);
bool CollisionRectCircle(const CRectangle rect, const CCircle cir);
void String(int sx, int sy, int fontsize, const char * str);
void String(int sx, int sy, int fontsize, const char * str, MofU32 color);
void String(int sx, int sy, int fontsize, const int& time);

class CCordinate {
private:
	static CRectangle m_StageRect;
	static Vector2*	  m_pPlayerPos;
	static Vector2*	  m_pMainCameraPos;
	static Vector2	  m_SavePos;
	static bool		  m_bCameraCntrl;
	static bool		  m_bBoss;
	static bool		  m_bKey;
	static bool		  m_bStop;
	static bool		  m_bSkip;
	static bool		  m_bBack;

public:
	static Vector2 GetSavePoint(void) { return m_SavePos; }
	static void SetSavePoint(const Vector2& pos) { m_SavePos = pos; }
	static void SetPlayerPos(Vector2* pPos) { m_pPlayerPos = pPos; }
	static void SetMainCameraPos(Vector2* pPos) { m_pMainCameraPos = pPos; }
	static Vector2 GetPlayerPos(void) { return *m_pPlayerPos; }
	static Vector2 GetMainCameraPos(void) { return *m_pMainCameraPos; }
	static CRectangle GetMainCameraRect(void) {
		return CRectangle(
			m_pMainCameraPos->x, m_pMainCameraPos->y,
			m_pMainCameraPos->x + g_pGraphics->GetTargetWidth(), m_pMainCameraPos->y + g_pGraphics->GetTargetHeight()
		);
	}
	static void SetStageRect(const CRectangle& rec) { m_StageRect = rec; }
	static CRectangle GetStageRect(void) { return m_bBoss ? GetMainCameraRect() : m_StageRect; }
	static bool IsCameraCntrl(void) { return m_bCameraCntrl; }
	static void SetCameraCntrl(const bool& b) { m_bCameraCntrl = b; }
	static bool IsBoss(void) { return m_bBoss; }
	static void SetBossFlag(const bool& b) { m_bBoss = b; }
	static bool IsKey(void) { return m_bKey; }
	static void SetKey(const bool& b) { m_bKey = b; }

	static void SetStop(const bool& b) { m_bStop = b; }
	static void SetSkip(const bool& b) { m_bSkip = b; }
	static void SetBack(const bool& b) { m_bBack = b; }

	static bool IsStopUI(void) { return m_bStop; }
	static bool IsSkipUI(void) { return m_bSkip; }
	static bool IsBackUI(void) { return m_bBack; }
};

#define NewPointerRelease(p)	\
	if (p)						\
	{							\
		delete p;				\
		p = nullptr;			\
	}
