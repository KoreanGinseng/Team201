/**
 * @file Atack_NOKONOKO.��
 * @brief �m�R�m�R�̍U��
 * @author �吼�i��
 * @date �X�V���i10/29�j
 */

#pragma once
#include	"EnemyAtack.h"

class CAtack_NOKONOKO :public CEnemyAtack {
private:
public:
	CAtack_NOKONOKO();
	~CAtack_NOKONOKO();
	void Initialize();
	void Update(float EnemyPosX, float EnemyPosY, bool EnemyRevers, float PlayerPosX, float PlayerPosY);
	void Render();
	void Release();
};
