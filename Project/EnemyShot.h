#pragma once
#include "Enemy.h"
#include "Shot.h"

class CEnemyShot :
	public CShot
{
private:
	CDynamicArray<CEnemy*>* m_pEnemyArrayPointer;
	CEnemy*					m_pEnemy;
public:
	CEnemyShot(void);
	virtual ~CEnemyShot(void);
	void Fire(const Vector2& startPos) override;
	void Initialize(void) override;
	void Update(void) override;
	void Render(const Vector2& screenPos) override;
};

