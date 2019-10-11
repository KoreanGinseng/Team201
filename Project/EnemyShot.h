#pragma once
#include	"Mof.h"


class  CEnemyShot
{
private:
	CTexture	m_pTexture;
	float		m_PosX;
	float		m_PosY;
	float		m_SpdX;
	float		m_SpdY;
	bool		m_bShow;
	float		m_Radian;
public:
	 CEnemyShot();
	~ CEnemyShot();
	void Initialize();
	void Fire(float px,float py,float sx,float sy,float pPosx,float pPosy);
	void Update();
	void Render();
	//void SetTexture(CTexture* pt) { m_pTexture = pt; }
	bool GetShow() { return m_bShow; }
	bool SetShow(bool bs) { m_bShow = bs; }
	//void Release();

};


