/**
 * @file Enemy_TERESA.h
 * @brief �e���T
 * @author �吼�i��
 * @date �X�V���i10/29�j
 */

#pragma once
#include	"EnemyMove.h"

class CENEMY_TERESA :public CEnemyMove {
private:
public:
	CENEMY_TERESA();
	~CENEMY_TERESA();
	void Initialize();
	void Update(float Xpos, float Ypos);
	void Render(float Xpos, float Ypos);
	void Release();
};