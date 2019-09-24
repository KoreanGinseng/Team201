#pragma once
#define Atacktime 3

enum ENEMYATACK {
	ATACK_KAMITUKI,
};

class CEnemyAtack {
private:
	float m_fAposX;
	float m_fAposY;
	float m_fTime;
	bool m_bShow;


public:
	CEnemyAtack();
	~CEnemyAtack();
	void Initialize();
	void KUpdate(float EposX,float EposY,bool ERevers);
	void Render();

};
