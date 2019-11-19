/**
 * @file Enemy_RIGHTHAND.h
 * @brief �E��
 * @author �吼�i��
 * @date �X�V���i11/19�j
 */

#pragma once
#include "_Onishi/EnemyMove.h"
#define	CrawlRange	100
#define CrawlRangeCenter 50
class CENEMY_RIGHTHAND :public CEnemyMove {
private:
	int m_CrawlRange;
	float m_CrawlRangeCount;
public:
	CENEMY_RIGHTHAND();
	~CENEMY_RIGHTHAND();
	void Initialize();
	void Update(float Xpos, float Ypos);
	void Render(float Xpos, float Ypos);
	void Release();
};
