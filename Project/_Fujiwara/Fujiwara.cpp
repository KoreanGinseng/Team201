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
	testx = 100;
	testy = 200;
	x = 300;
	y = 200;
	tester = false;

}

/*****************************************************************
 * @fn
 * 更新
 * @param なし
 * @return なし
 *****************************************************************/
void CFujiwara::Update() {
	if (g_pInput->IsKeyHold(MOFKEY_A))
	{
		testx -= 10;
	}
	if (g_pInput->IsKeyHold(MOFKEY_D))
	{
		testx += 10;
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
	String(0, 0, FONT_SIZE, "ABC");
	CRectangle ts(testx, testy, testx + 10, testy + 10);
	CRectangle tss(x, y, x + 10, y + 10);
	CGraphicsUtilities::RenderFillRect(tss, MOF_XRGB(0, 255, 0));
	CGraphicsUtilities::RenderFillRect(ts, MOF_XRGB(255, 0, 0));
	test(ts,tss);
	CGraphicsUtilities::RenderString(10,40,"D=%s",(hit)?"true":"false");
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
}

void CFujiwara::String(int sx, int sy, int fontsize, const char * str)
{
	for (int i = 0; str[i] != '\0'; i++)
	{
		X = str[i] % 16;
		Y = ((str[i] - 32)/ 16);
		CRectangle SRect(X * 64, Y * 64,
						 X * 64 + 64, Y * 64 + 64);
		m_pFontTexture->RenderScale(sx, sy, fontsize/64.0, SRect);
		//m_pFontTexture->Render(sx, sy, SRect);
		sx += fontsize;
	}
}

void CFujiwara::test(CRectangle r, CRectangle o)
{
	CRectangle prec = r;
	CRectangle enec = o;
	

	if (prec.CollisionRect(enec))
	{
		hit = true;
	}
	else
	{
		hit = false;
	}
}