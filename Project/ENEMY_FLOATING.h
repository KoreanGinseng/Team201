/**
 * @file Enemy_FLOATING.h
 * @brief 跳弾
 * @author 大西永遠
 * @date 更新日（11/12）
 */

#pragma once
#include "_Onishi/EnemyMove.h"
#define	CrawlRange	100
#define CrawlRangeCenter 50
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
