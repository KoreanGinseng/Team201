/**
 * @file Enemy_BAT.h
 * @brief 蝙蝠の動き
 * @author 大西永遠
 * @date 更新日（11/12）
 */

#pragma once
#include	"EnemyMove.h"
#define	Bat_Atack_Range 200
//下方向の加速
#define Acceleration 2

class CENEMY_BAT :public CEnemyMove {
private:
	CSpriteMotionController m_Motion;
	CRectangle				m_SrcRect;
	CTexture	m_Texture;
public:
	CENEMY_BAT();
	~CENEMY_BAT();
	void Initialize();
	void Update(float Xpos, float Ypos);
	void Render(float Xpos, float Ypos);
	void Release();
};
