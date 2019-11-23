#pragma once
#include "Character.h"

class CBackChip :
	public CCharacter
{
private:
	int m_RenderType;
public:
	CBackChip();
	~CBackChip();
	void RenderBackBack(const Vector2& screenPos);
	void RenderBackStage(const Vector2& screenPos);
	void SetRenderType(const int& t) { m_RenderType = t; }
	int GetRenderType(void) const { return m_RenderType; }
};

