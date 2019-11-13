#include "UI.h"



UI::UI()
{
}


UI::~UI()
{
}

void UI::Initialize(void)
{
}

void UI::Update(void)
{
}

void UI::Render(int ghp)
{
	ui1 = g_pTextureManager->GetResource("test_heart.png");
	int y = g_pGraphics->GetTargetHeight() - ui1->GetHeight()-64;
	RenHp(ghp,0,y);
	CTexturePtr ui2 = g_pTextureManager->GetResource("UI02.png");
	int y2 = g_pGraphics->GetTargetHeight() - ui2->GetHeight();
	int x2 = g_pGraphics->GetTargetWidth() - ui2->GetWidth();
	ui2->Render(x2, y2 - 64);
}

void UI::Release(void)
{

}



void UI::RenHp(int hp, int hx, int hy)
{
	int w = ui1->GetWidth();
	CRectangle rec(0, 0, w / 2, ui1->GetHeight());
	if (hp != 1)
	{
		for (float i = 0; i < hp / 2; i++)
		{
			if (hp % 2 == 1)
			{
				/*m_pHeatTexture.Render(hx + hp / 2 * w, hy, rec);
				m_pHeatTexture.Render(hx + i * w, hy);*/
				
				int y = g_pGraphics->GetTargetHeight() - ui1->GetHeight();
				ui1->Render(hx + hp / 2 * w, hy, rec);
				ui1->Render(hx + i * w, hy);
			}
			else
			{
				ui1->Render(hx + i * w, hy);
			}
		}
	}
	else
	{
		ui1->Render(hx, hy, rec);
	}
}