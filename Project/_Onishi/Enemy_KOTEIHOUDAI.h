/**
 * @file Enemy_KOTEIHOUDAI.h
 * @brief 固定砲台
 * @author 大西永遠
 * @date 更新日（10/29）
 */

#pragma once
#include	"EnemyMove.h"
class CENEMY_KOTEIHOUDAI :public CEnemyMove {
private:
	float m_fAtackTimer;
	float m_fCooltime;
public:
	CENEMY_KOTEIHOUDAI();
	~CENEMY_KOTEIHOUDAI();
	void Initialize();
	void Update(float Xpos, float Ypos);
	void Render(float Xpos, float Ypos);
	void Release();
};

