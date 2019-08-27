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


public:
			CPlayer();
			~CPlayer();
	bool	Load(void);
	void	Initialize(void);
	void	Update(void);
	void	Render(void);
	void	Release(void);

	void	RenderDebug(void);
	void	RenderState(void);
	void	PadOperation(void);
	void	LifeDecrease(void);

};