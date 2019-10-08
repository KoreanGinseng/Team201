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
	virtual ~CEnemyAtack();
	virtual void Initialize()=0;
	virtual void Update(float EnemyPosX,float EnemyPosY,bool EnemyRevers)=0;
	virtual void Render()=0;

};
