#pragma once

#include		"Mof.h"
#include		"GamePad.h"

//#define		PLAYER_WIDTH	60
//#define		PLAYER_HEIGHT	64
//
//#define		PLAYER_MAXHP	100
//
//#define		PLAYER_MAXLIFE	3
//
//#define		PLAYER_MAXSPEED	8
//
//#define		PLAYER_GRAVITY	0.3f

class CPlayer {



private:
	CTexture		m_Texture;
	CTexture		m_HpTexture;


	bool			m_bJump;

	int				m_Life;
	int				m_Hp;

	float			m_PosX;
	float			m_PosY;

	float			m_MoveX;
	float			m_MoveY;

	float			m_MoveX2;
	float			m_MoveY2;

	//åÆÇéùÇ¡ÇƒÇ¢ÇÈÇ©Ç¢Ç»Ç¢Ç©ÇîªíËÇ∑ÇÈÉtÉâÉO
	bool			KeyFlag;
	bool			MoveCh;

	float GRa_;

public:
			CPlayer();
			~CPlayer();
	bool	Load(void);
	void	Initialize(void);
	void	Update(void);
	void	Render(Vector2 scroll);
	void	Release(void);

	void	RenderDebug(void);
	void	RenderState(void);
	void	PadOperation(void);
	void	KeyOperation(void);
	void	LifeDecrease(void);

	void	CollisionStage(Vector2 o);
	void	KeyTrue(void);
	void	KeyFalse(void);

	CRectangle GetRect() { return CRectangle(m_PosX, m_PosY, m_PosX + 60, m_PosY + 64); }
	Vector2 GetPos() { return Vector2(m_PosX, m_PosY); }
	Vector2 GetMove() { return Vector2(m_MoveX, m_MoveY); }
	Vector2 GetMove2() { return Vector2(m_MoveX2, m_MoveY2); }

	//í«â¡
	bool GetKey() { return KeyFlag; }

	void Gra_Set();
	void Gra_zero();
	
	void Pmove();
	
};