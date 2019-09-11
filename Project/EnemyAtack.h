#pragma once
#include "mof.h"


enum ENEMYATACK {
	ATACK_KAMITUKI,
};

class CEnemyAtack {
private:
	float AposX;
	float AposY;
	bool m_bShow;

public:
	CEnemyAtack();
	~CEnemyAtack();
	void Initialize();
	void KUpdate();
	void Render();

};

