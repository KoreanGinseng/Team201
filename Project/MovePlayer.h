#pragma once
#include "Move.h"
#include "GameDefine.h"

class CMovePlayer :
	public CMove
{
private:
	bool m_bMove;
	bool m_bJump;
	bool m_bJumpUp;
	bool m_bJumpDown;
	bool m_bClime;
public:
	CMovePlayer();
	~CMovePlayer();
	void Initialize(void) override;
	void Update(void) override;
	void SetClime(const bool& b) { m_bClime = b; }
	void ResetJump(void) { if (m_bJump) m_bJump = false; m_bJumpDown = false; m_bJumpUp = false; }
	bool GetJump(void) const { return m_bJump; }
	bool GetJumpUp(void) const { return m_bJumpUp; }
	bool GetJumpDown(void) const { return m_bJumpDown; }
private:
	void PadOparation(void);
	void KeyOparation(void);
};

