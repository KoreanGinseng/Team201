/**
 * @file EnemyShot.h
 * @brief エネミーの弾
 * @author 大西永遠
 * @date 更新日（11/15）
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
	bool		m_ClonFrag;
	bool		m_TleEnd;
	float		m_StopTime;
	bool		m_Wall;
	
public:
	 CEnemyShot();
	virtual ~ CEnemyShot();
	virtual void Initialize()=0;
	virtual void Fire(float px,float py,float sx,float sy,float pPosx,float pPosy)=0;
	virtual void CloningFire(float px, float py, float sx, float sy, float pPosx, float pPosy, float rd,float ddx,float ddy) {};
	virtual void Update()=0;
	virtual void Render()=0;
	virtual void Release()=0;
	//void SetTexture(CTexture* pt) { m_pTexture = pt; }
	bool GetShow() { return m_bShow; }
	bool SetShow(bool bs) { m_bShow = bs; }
	//void Release();
	virtual void CollisionStage(float ox, float oy)=0;

	float GetEraseTime() { return m_EraseTime; }
	float GetRadian(float px, float py, float pPosx, float pPosy) {
		float dx = pPosx - px;
		float dy = pPosy - py;
		m_Radian = atan2f(dy, dx);
		m_Radian = MOF_ToDegree(m_Radian);
		return m_Radian;
	}
	float Getddx(float px, float py, float pPosx, float pPosy){
		float dx = pPosx - px;
		float dy = pPosy - py;
		float Playerdx;
		float Playerdy;
		float d;
		float ddx=0;
		float ddy=0;

		Playerdx = pPosx - px;
		Playerdy = pPosy - py;
		d = sqrt(Playerdx*Playerdx + Playerdy * Playerdy);
		ddx = dx / d;
		return ddx;
	}
	float Getddy(float px, float py, float pPosx, float pPosy) {
		float dx = pPosx - px;
		float dy = pPosy - py;
		float Playerdx;
		float Playerdy;
		float d;
		float ddx;
		float ddy;

		Playerdx = pPosx - px;
		Playerdy = pPosy - py;
		d = sqrt(Playerdx*Playerdx + Playerdy * Playerdy);
		ddy = dy / d;
		return ddy;
	}

	bool SetFrag(bool bs) { return m_ClonFrag = bs; }
	bool GetTleEnd() { return m_TleEnd; }
	bool GetStop() { return m_StopTime; }
	bool GetWall() { return m_Wall; }

};


