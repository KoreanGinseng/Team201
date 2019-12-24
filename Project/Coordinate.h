#pragma once
#include	"Mof.h"
#include	"GameDefine.h"
#include	"Camera2D.h"

//関数のプロトタイプ宣言
Vector2 WorldTransration(Vector2 cp, Vector2 sp);
Vector2 ScreenTransration(Vector2 cp, Vector2 wp);
bool CollisionRectCircle(const CRectangle rect, const CCircle cir);
void String(int sx, int sy, int fontsize, const char * str);
void String(int sx, int sy, int fontsize, const int& time);

class CCordinate {
private:
	static CRectangle m_StageRect;
	static Vector2*	  m_pPlayerPos;
	static Vector2*	  m_pMainCameraPos;
	static Vector2	  m_SavePos;
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
	static CRectangle GetStageRect(void) { return m_StageRect; }
};

#define NewPointerRelease(p)	\
	if (p)						\
	{							\
		delete p;				\
		p = nullptr;			\
	}
