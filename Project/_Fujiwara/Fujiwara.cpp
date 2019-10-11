/*****************************************************************
 *	@file			Fujiwara.cpp
 *	@brief			フジワラシーン実装
 *	@author			井上颯騎
 *	@date			2019/07/29
 *****************************************************************/

//! INCLUDE
#include	"Fujiwara.h"


/*****************************************************************
 * @fn
 * 引数なしコンストラクタ
 * @param なし
 * @return なし
 *****************************************************************/
CFujiwara::CFujiwara() :
CSceneBase() {
}

/*****************************************************************
 * @fn
 * 引数なしデストラクタ
 * @param なし
 * @return なし
 *****************************************************************/
CFujiwara::~CFujiwara() {
	Release();
}

/*****************************************************************
 * @fn
 * 必要な素材の読み込み
 * @param なし
 * @return なし
 *****************************************************************/
void CFujiwara::Load() {
	//リソース配置ディレクトリの設定
	CUtilities::SetCurrentDirectory("Resource");
	m_pFontTexture = new CTexture();
	m_pFontTexture->Load("sumple_imvisible.png");
	m_pHeatTexture.Load("test_heart.png");
}

/*****************************************************************
 * @fn
 * 初期化
 * @param なし
 * @return なし
 *****************************************************************/
void CFujiwara::Initialize() {
	X = 0;
	Y = 0;
	Lenth = 0;
	num = 0;
	
	Hposx = INI_X;
	Hposy = INI_Y;
	HP = MAX_HEART*2;

}

/*****************************************************************
 * @fn
 * 更新
 * @param なし
 * @return なし
 *****************************************************************/
void CFujiwara::Update() {
	
	num += 1;

	//ダメージ処理？
	if (g_pInput->IsKeyPush(MOFKEY_RETURN)&&HP>0)
	{
		HP -=1;
	}

}

/*****************************************************************
 * @fn
 * 描画
 * @param なし
 * @return なし
 *****************************************************************/
void CFujiwara::Render() {
	//m_pFontTexture->RenderScale(0, 0, FONT_SIZE/64);
	
	String(g_pGraphics->GetTargetWidth()-64, 0, FONT_SIZE,num);
	RenHp(HP, Hposx, Hposy);
	
	CGraphicsUtilities::RenderString(10, 10, "%d",HP);
}

/*****************************************************************
 * @fn
 * デバッグ描画
 * @param なし
 * @return なし
 *****************************************************************/
void CFujiwara::RenderDebug() {
	
}

/*****************************************************************
 * @fn
 * 解放
 * @param なし
 * @return なし
 *****************************************************************/
void CFujiwara::Release() {
	m_pFontTexture->Release();
	m_pHeatTexture.Release();
}

void CFujiwara::String(int sx, int sy, int fontsize, const char * str)
{
	for (int i = 0; str[i] != '\0'; i++)
	{
		X = str[i] % 16;
		Y = ((str[i] - 32)/ 16);
		CRectangle SRect(X * 64, Y * 64,
						 X * 64 + 64, Y * 64 + 64);
		sx += fontsize;
		m_pFontTexture->RenderScale(sx, sy, fontsize/64.0, SRect);
	}
	
}

void CFujiwara::String(int sx, int sy, int fontsize, const int& time)
{
	std::string str;
    str = std::to_string(time);
	
	size_t size = str.length() - 1;
	for (int i = 0; str[i] != '\0'; i++)
	{
		X = str[i] % 16;
		Y = ((str[i] - 32) / 16);
		CRectangle SRect(X * 64, Y * 64,
			X * 64 + 64, Y * 64 + 64);
		sx += fontsize;
		m_pFontTexture->RenderScale(sx - size * fontsize, sy, fontsize / 64.0, SRect);//(表示座標ｘ,表示座標y,拡大率,rect)
	}
	
}

/*
  int hp=現在のHP
  int hx=HPの表示位置（x座標）
　int hy=HPの表示位置（y座標)
*/
void CFujiwara::RenHp(int hp, int hx, int hy)
{
	int w = m_pHeatTexture.GetWidth();
	CRectangle rec(0, 0, w/2, m_pHeatTexture.GetHeight());
	if (hp != 1)
	{
		for (float i = 0; i < hp/ 2; i++)
		{
			if (hp % 2 == 1)
			{
				m_pHeatTexture.Render(hx+ hp / 2 *w, hy, rec);
				m_pHeatTexture.Render(hx+ i * w,hy);
			}
			else
			{
				m_pHeatTexture.Render(hx + i * w, hy);
			}
		}
	}
	else
	{
		m_pHeatTexture.Render(hx, hy, rec);
	}
}

