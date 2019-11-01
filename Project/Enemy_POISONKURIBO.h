/**
 * @file Enemy_POISONKURIBIO.h
 * @brief �ŃN���{�[
 * @author �吼�i��
 * @date �X�V���i11/1�j
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
