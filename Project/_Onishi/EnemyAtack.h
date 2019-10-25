#pragma once
#include	"../GameDefine.h"
#include	"EnemyDefine.h"

#define Atacktime 3

enum ENEMYATACK {
	ATACK_KAMITUKI,
};

class CEnemyAtack {
protected:
	float m_fAtackPosX;
	float m_fAtackPosY;
	float m_fTime;
	bool m_bShow;
public:
	CEnemyAtack();
	~CEnemyAtack();
	void Initialize();
	void KUpdate(float EposX,float EposY,bool ERevers);
	void Render();

};
