#pragma once
#include	"Mof.h"
#include	"GameDefine.h"

//関数のプロトタイプ宣言
Vector2 WorldTransration(Vector2 cp, Vector2 sp);
Vector2 ScreenTransration(Vector2 cp, Vector2 wp);
bool CollisionRectCircle(const CRectangle rect, const CCircle cir);
void String(int sx, int sy, int fontsize, const char * str);
void String(int sx, int sy, int fontsize, const int& time);

class CCordinate {
private:
	static CRectangle m_StageRect;
public:
	static void SetStageRect(const CRectangle& rec) { m_StageRect = rec; }
	static CRectangle GetStageRect(void) { return m_StageRect; }
};

#define NewPointerRelease(p)	\
	if (p)						\
	{							\
		delete p;				\
		p = nullptr;			\
	}
