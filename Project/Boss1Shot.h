#pragma once
#include "Shot.h"
class CBoss1Shot1 :
	public CShot
{
private:
	int	m_Bound;
	std::string m_TexName;
	Vector2 m_ExPos;
public:
	CBoss1Shot1(void);
	virtual ~CBoss1Shot1(void);
	void Initialize(void) override;
	void Update(void) override;
	void Render(const Vector2& screenPos) override;
	void Fire(const Vector2& pos) override;
	virtual void	CollisionPlayer(const Vector2& over) override;
	void CollisionStage(const Vector2& over) override;
	virtual CRectangle GetRect(void) override;
};

