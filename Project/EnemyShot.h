#pragma once
#include "Enemy.h"
#include "EnemyPoison.h"
#include "Shot.h"

class CEnemyShot :
	public CShot
{
private:
	CDynamicArray<CEnemy*>* m_pEnemyArrayPointer;
	CEnemy*					m_pEnemy;
	Vector2					m_WarpPos[5];
	int						m_WarpTime;
	int						m_No;
	int						m_OffsetWarpTime;
	int						m_DeadTime;
	Vector2					m_EneMove;
public:
	CEnemyShot(void);
	virtual ~CEnemyShot(void);
	void Fire(const Vector2& startPos) override;
	void Initialize(void) override;
	void Update(void) override;
	void Render(const Vector2& screenPos) override;
	void SetArray(CDynamicArray<CEnemy*>* pArray);
	void SetWorpTime(const int& time);
};

