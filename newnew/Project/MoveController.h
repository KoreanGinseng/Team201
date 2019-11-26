#pragma once
#include	"GameDefine.h"
#include	"Move.h"
#include	"Anim.h"
#include	"MovePlayer.h"
#include	"MoveMash.h"
#include	"MoveBackChip.h"

class CMoveController
{
private:
	CMove*	m_pMove;
public:
	CMoveController();
	~CMoveController();
	void Initialize(void);
	void Update(void);
	bool Create(const int& no);
	Vector2 GetMove(void) const {return m_pMove->GetMove(); }
	Vector2 GetSpd(void) const { return m_pMove->GetSpd(); }
	int GetMotionNo(void) const { return m_pMove->GetMotionNo(); }
	CMove*  GetInstance(void) { return m_pMove; }
	void SetMove(const float& x, const float& y) { SetMove(Vector2(x, y)); }
	void SetMove(const Vector2& move) { m_pMove->SetMove(move); }
	void SetSpd(const float& x, const float& y) { SetSpd(Vector2(x, y)); }
	void SetSpd(const Vector2& spd) { m_pMove->SetSpd(spd); }
	void Remove(void) { NewPointerRelease(m_pMove); }
	bool GetReverse(void) const { return m_pMove->GetReverse(); }
	void MoveReverse(void) { m_pMove->MoveReverse(); }
};

