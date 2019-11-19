#pragma once
#include "Move.h"
#include "GameDefine.h"

class CMovePlayer :
	public CMove
{
private:
	bool m_bMove;
	bool m_bJump;
	bool m_bClime;
	bool m_bReverse;
public:
	CMovePlayer();
	~CMovePlayer();
	void Initialize(void) override;
	void Update(void) override;
	void SetClime(const bool& b) { m_bClime = b; }
	void ResetJump(void) { if(m_bJump) m_bJump = false; }
	bool GetReverse(void) const { return m_bReverse; }
private:
	void PadOparation(void);
	void KeyOparation(void);
};

