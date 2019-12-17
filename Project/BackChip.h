#pragma once
#include "Character.h"
#include "Stage.h"

class CBackChip :
	public CCharacter
{
private:
	Vector2 m_StartPos;
	int m_RenderType;
public:
	CBackChip();
	~CBackChip();
	void Initialize(void) override;
	void Update(void) override;
	void RenderBackBack(const Vector2& screenPos);
	void RenderBackStage(const Vector2& screenPos);
	void SetRenderType(const int& t) { m_RenderType = t; }
	int GetRenderType(void) const { return m_RenderType; }
};

