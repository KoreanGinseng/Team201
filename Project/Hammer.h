#pragma once
#include "TargetObj.h"
class CHammer :
	public CTargetObj
{
private:
	CTexturePtr m_pHummerTexture;
	//cos‚Ì”g‚Ì‘¬“x
	float m_CosSpd;
	float* m_pRectCenter;
	float deg;
	//cos‚Ì”g
	float m_CosTime;
	float m_Rote;
	Vector2 m_HummerPos;
public:
	CHammer(void);
	virtual ~CHammer(void);
	void Initialize(void) override;
	void Update(void) override;
	void Render(const Vector2& screenPos) override;

	Vector2	GetRectCenter(void);
	CRectangle GetRect(void) override;
	bool OverValue(CRectangle rect, Vector2& out) override;
};

