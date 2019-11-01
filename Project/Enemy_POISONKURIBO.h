/**
 * @file Enemy_POISONKURIBIO.h
 * @brief 毒クリボー
 * @author 大西永遠
 * @date 更新日（11/1）
 */

#pragma once
#include	"_Onishi/EnemyMove.h"
#include	"EnemyDefine.h"

class CEnemy_POISONKURIBO :public CEnemyMove {
private:
	CEnemyAtack*	m_Atack;
	CSpriteMotionController m_Motion;
	CRectangle				m_SrcRect;
	CTexture	m_Texture;
	bool		m_bShow;
public:
	CEnemy_POISONKURIBO();
	~CEnemy_POISONKURIBO();
	void Initialize();
	void Update(float Xpos, float Ypos);
	void Render(float Xpos, float Ypos);
	void Release();
};
