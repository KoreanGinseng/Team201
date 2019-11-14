/**
 * @file RayBullet.h
 * @brief　光線
 * @author 大西永遠
 * @date 更新日（11/14）
 */

#pragma once
#include "EnemyShot.h"
#include "EnemyDefine.h"
#define	ReflectTime 4


class CRayBullet :public CEnemyShot {
private:
	int m_BounceTimes;
	CRectangle				m_SrcRect;
	CTexture	m_Texture;
	float m_ScaleMagnification[ReflectTime-1];
	float m_RPosX[ReflectTime];
	float m_RPosY[ReflectTime];
	float		m_RRadian[ReflectTime-1];
public:
	CRayBullet();
	~CRayBullet();
	void Initialize();
	void Fire(float px, float py, float sx, float sy, float pPosx, float pPosy);
	void Update();
	void Render();
	void Release();
	void CollisionStage(float ox, float oy);
	void SetPos();
	void SetRadius(float posx,float posy, float posx2, float posy2,int i);
	void SetDistance(float posx, float posy, float posx2, float posy2,int i);
};
