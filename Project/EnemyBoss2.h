#pragma once
#include "Enemy.h"
#include "RayShot.h"

class CEnemyBoss2 :
	public CEnemy
{
private:
	enum BODY {
		BODY_HEAD,
		BODY_BODY,
		BODY_DOWN,
		BODY_COUNT
	};
	CSpriteMotionController	m_BodyMotion[BODY_COUNT];
	CSpriteMotionController	m_DeadMotion;
	bool					m_bBodyDead[BODY_COUNT];
	Vector2					m_BodyPos[BODY_COUNT];
	CTexturePtr				m_pBodyTexture[BODY_COUNT * 2];
	CTexturePtr				m_pDeadTexture;
	bool					m_bDeadM;
	CRayShot				m_RayShot;
public:
	CEnemyBoss2(void);
	~CEnemyBoss2(void);
	virtual void CreateMotion(const char* pName) override;
	virtual void SetTexture(const CTexturePtr& pt) override;
	virtual void Initialize(void) override;					//èâä˙âª
	virtual void Update(void) override;						//çXêV
	virtual void Render(const Vector2& screenPos) override;	//ï`âÊ
	virtual void RenderCircle(const Vector2& screenPos);	//Circleï`âÊ
	virtual void Release(void) override;					//âï˙
	bool CollisionRayShot(const CCircle& shot);
};

