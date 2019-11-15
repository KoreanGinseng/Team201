/**
 * @file EnemyShot.h
 * @brief �G�l�~�[�̒e
 * @author �吼�i��
 * @date �X�V���i11/15�j
 */

#pragma once
#include	"Mof.h"


class  CEnemyShot
{
private:
protected:
	CTexture	m_pTexture;
	float		m_PosX;
	float		m_PosY;
	float		m_SpdX;
	float		m_SpdY;
	bool		m_bShow;
	float		m_Radian;
	float		m_EraseTime;
public:
	 CEnemyShot();
	virtual ~ CEnemyShot();
	virtual void Initialize()=0;
	virtual void Fire(float px,float py,float sx,float sy,float pPosx,float pPosy)=0;
	virtual void Update()=0;
	virtual void Render()=0;
	virtual void Release()=0;
	//void SetTexture(CTexture* pt) { m_pTexture = pt; }
	bool GetShow() { return m_bShow; }
	bool SetShow(bool bs) { m_bShow = bs; }
	//void Release();
	virtual void CollisionStage(float ox, float oy)=0;

	float GetEraseTime() { return m_EraseTime; }
};


