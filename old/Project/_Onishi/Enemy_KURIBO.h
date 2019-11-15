/**
 * @file Enemy_KURIBIO.h
 * @brief �N���{�[
 * @author �吼�i��
 * @date �X�V���i10/29�j
 */

#pragma once
#include	"EnemyMove.h"

class CEnemy_KURIBO :public CEnemyMove {
private:
public:
	CEnemy_KURIBO();
	~CEnemy_KURIBO();
	void Initialize();
	void Update(float Xpos, float Ypos);
	CRectangle	GetRect(void) const {
		CRectangle rect(m_fXpos, m_fYpos, m_fXpos + m_SrcRect.GetWidth(), m_fYpos + m_SrcRect.GetHeight());
		return rect;
	}
};