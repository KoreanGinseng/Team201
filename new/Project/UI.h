#pragma once
#include	"GameDefine.h"
class UI
{
private:
	CTexturePtr ui1;
public:
	UI();
	~UI();

	void Initialize(void);
	void Update(void);
	void Render(int ghp);
    void Release(void);

	void RenHp(int hp, int hx, int hy);
};

