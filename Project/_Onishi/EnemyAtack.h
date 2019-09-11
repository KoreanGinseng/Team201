#pragma once
#define Atacktime 3

enum ENEMYATACK {
	ATACK_KAMITUKI,
};

class CEnemyAtack {
private:
	float AposX;
	float AposY;
	float time;
	bool m_bShow;


public:
	CEnemyAtack();
	~CEnemyAtack();
	void Initialize();
	void KUpdate(float EposX,float EposY,bool ERevers);
	void Render();

};
