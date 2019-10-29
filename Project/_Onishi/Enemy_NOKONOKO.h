/**
 * @file Enemy_NOKONOKO.h
 * @brief �m�R�m�R
 * @author �吼�i��
 * @date �X�V���i10/29�j
 */

#pragma once
#include	"EnemyMove.h"

class CENEMY_NOKONOKO :public CEnemyMove {
private:
	float m_fTimer;
public:
	CENEMY_NOKONOKO();
	~CENEMY_NOKONOKO();
	void Initialize();
	void Update(float Xpos, float Ypos);
	void Render(float Xpos, float Ypos);
	void Release();
};
