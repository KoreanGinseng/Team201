/**
 * @file Enemy_RIGHTHAND.h
 * @brief 右手
 * @author 大西永遠
 * @date 更新日（11/19）
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
