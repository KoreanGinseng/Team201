#pragma once
#include	"GameDefine.h"
#include	"Move.h"
#include	"Anim.h"

class CMoveController
{
private:
	CDynamicArray<CMove*>	m_MoveArray;
	CAnim					m_Anim;
public:
	CMoveController();
	~CMoveController();
	void Initialize(void);
	void Update(void);
	
	void MotionCreate(const char* pName) { m_Anim.Create(pName); }
	CAnim GetAnim(void) const { return m_Anim; }
	void AddMove(CMove* pm) { m_MoveArray.Add(pm); }
	void RemoveMove(CMove* pm) { m_MoveArray.Delete(&pm); }

};

