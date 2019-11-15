#pragma once
#include "Object.h"
#include "MoveController.h"
#include "Anim.h"

class CCharacter :
	public CObject
{
protected:
	CMoveController		m_MvCntrl;
	CAnim				m_Anim;
	RectArray			m_RectArray;
	bool				m_bDead;
public:
	CCharacter(void);
	~CCharacter(void) override;
	void Initialize(void) override;
	void Update(void) override;
	void Render(const Vector2& screenPos) override;
	void Release(void) override;

	template<typename T >
	void CreateMove(T* p) { m_MvCntrl.Create(p); }
	void CreateAnim(const char* pName) { m_Anim.Create(pName); }

	bool IsDead(void) const { return m_bDead; }

	Vector2 GetPos(void) const { return m_Pos; }
	CRectangle GetSrcRect(void) const { return m_Anim.GetRect(); }
	virtual CRectangle GetRect(void) const { return CRectangle(m_Pos.x, m_Pos.y, m_Pos.x + GetSrcRect().GetWidth(), m_Pos.y + GetSrcRect().GetHeight()); }
	RectArray GetRectArray(void) const { return m_RectArray; }
};

