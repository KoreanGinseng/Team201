#pragma once
#include "Object.h"

class CMapObj :
	public CObject
{
public:
	CMapObj();
	~CMapObj();
	void Initialize(void) override;
	void Update(void) override;
	void Render(const Vector2& screenPos) override;
	void Release(void);
};

