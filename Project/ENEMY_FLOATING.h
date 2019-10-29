/**
 * @file Enemy_FLOATING.h
 * @brief ���e
 * @author �吼�i��
 * @date �X�V���i10/29�j
 */

#pragma once
#include "_Onishi/EnemyMove.h"

class CENEMY_FLOATING :public CEnemyMove {
private:
	int m_CrawlRange;
	float m_CrawlRangeCount;
public:
	CENEMY_FLOATING();
	~CENEMY_FLOATING();
	void Initialize();
	void Update(float Xpos, float Ypos);
	void Render(float Xpos, float Ypos);
	void Release();
};
