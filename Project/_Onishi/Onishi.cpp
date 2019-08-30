/*****************************************************************
 *	@file			Onishi.cpp
 *	@brief			オオニシシーン実装
 *	@author			井上颯騎
 *	@date			2019/07/29
 *****************************************************************/

//! INCLUDE
#include	"Onishi.h"

/*****************************************************************
 * @fn
 * 引数なしコンストラクタ
 * @param なし
 * @return なし
 *****************************************************************/
COnishi::COnishi() :
CSceneBase() {
}

/*****************************************************************
 * @fn
 * 引数なしデストラクタ
 * @param なし
 * @return なし
 *****************************************************************/
COnishi::~COnishi() {
	Release();
}

/*****************************************************************
 * @fn
 * 必要な素材の読み込み
 * @param なし
 * @return なし
 *****************************************************************/
void COnishi::Load() {

}

/*****************************************************************
 * @fn
 * 初期化
 * @param なし
 * @return なし
 *****************************************************************/
void COnishi::Initialize() {
	poase = false;
	time = 0;
	Xpos = 100;
	Ypos = 100;
	atack = false;
	MXpos = 0;
	MYpos = 0;
	h = false;
	getxpos = 0;
	getypos = 0;
	getx = 0;
	gety = 0;
	Revers = false;

	gEnemy.Initialize();
	gEnemytype = ENEMY_TERESA;
}

/*****************************************************************
 * @fn
 * 更新
 * @param なし
 * @return なし
 *****************************************************************/
void COnishi::Update() {
	
	if (g_pInput->IsKeyPush(MOFKEY_F4)) {
		poase = !poase;
	}
	if (poase) {
		return;
	}
	g_pInput->GetMousePos(MXpos, MYpos);
	
	if (!atack) {
		if (g_pInput->IsKeyHold(MOFKEY_UP)) {
			Ypos -= spead;
		}
		else if (g_pInput->IsKeyHold(MOFKEY_DOWN))
		{
			Ypos += spead;
		}
		if (g_pInput->IsKeyHold(MOFKEY_LEFT)) {
			Xpos -= spead;
			Revers = true;
		}
		else if (g_pInput->IsKeyHold(MOFKEY_RIGHT))
		{
			Xpos += spead;
			Revers = false;
		}
		if (g_pInput->IsKeyPush(MOFKEY_B)) {
			atack = !atack;
		}
	}
	else {
		
		if (g_pInput->IsKeyPush(MOFKEY_B)) {
			atack = !atack;
		}
	}
	
	time += 1 * CUtilities::GetFrameSecond();
	float gx = getxpos - Xpos;
	float gy = getypos - Ypos;
	float v = sqrtf(gx*gx + gy * gy);
	gx /= v;
	gy /= v;
	if (h) {
		
		getx += gx*10;
		gety += gy*10;
	}
	if (!h) {
		getx = 0;
		gety = 0;
	}

	if (g_pInput->IsKeyPush(MOFKEY_RETURN)) {
		if (gEnemytype == ENEMY_KURIBO) {
			gEnemytype = ENEMY_NOKONOKO;
		}
		else if (gEnemytype == ENEMY_NOKONOKO) {
			gEnemytype = ENEMY_TERESA;
		}
		else {
			gEnemytype = ENEMY_KURIBO;
		}
	}
	switch (gEnemytype)
	{
		case ENEMY_KURIBO:
			gEnemy.KUpdate();
			break;
		case ENEMY_NOKONOKO:
			gEnemy.NUpdate();
			break;
		case ENEMY_TERESA:
			gEnemy.TUpdate(Xpos,Ypos,Revers);
			break;
	}


}

/*****************************************************************
 * @fn
 * 描画
 * @param なし
 * @return なし
 *****************************************************************/
void COnishi::Render() {
	float x = (MXpos - Xpos);
	float y = (MYpos - Ypos);
	



	float tx = sqrtf(x*x);
	float ty = sqrtf(y*y);

	if (MXpos<=Xpos) {
		tx = -tx;
	}

	if (MYpos<=Ypos) {
		ty = -ty;
	}

	float a = tx / ty;
	float ax = MYpos/a;
	float ay = a*MXpos;
	

	float c = sqrtf(x * x + y * y);

	float cx = x / c;
	float cy = y / c;
	
	


	CGraphicsUtilities::RenderString(g_pGraphics->GetTargetWidth()/4*3,0,MOF_COLOR_BLACK, "タイム：%.1f",time);
	CGraphicsUtilities::RenderFillCircle(Xpos, Ypos, 10, MOF_COLOR_BLACK);
	if (atack) {
		CGraphicsUtilities::RenderLine(Xpos, Ypos, tx*1000, ty*1000, MOF_COLOR_WHITE);
		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON)) {
			getxpos = MXpos;
			getypos = MYpos;
			h = !h;
		}
	}
	if (h) {
		CGraphicsUtilities::RenderFillCircle(Xpos+getx,Ypos+gety, 30, MOF_COLOR_GREEN);
		
	}
	/*if (h) {
	
			CGraphicsUtilities::RenderFillRect(, MOF_COLOR_GREEN);
		
	}
	else {
		CGraphicsUtilities::RenderFillRect(, MOF_COLOR_RED);
	}*/
	if (poase) {
		CGraphicsUtilities::RenderFillRect(g_pGraphics->GetTargetWidth() / 4, g_pGraphics->GetTargetHeight() / 3, 700, 600, MOF_COLOR_WHITE);
	}

	gEnemy.Render();

	switch (gEnemytype)
	{
	case ENEMY_KURIBO:
		CGraphicsUtilities::RenderString(100,0,"クリボー スペースで攻撃、死亡");
		break;
	case ENEMY_NOKONOKO:
		CGraphicsUtilities::RenderString(100, 0, "ノコノコ スペースで攻撃、5秒後に動き出す、攻撃した後にAで死亡");
		break;
	case ENEMY_TERESA:
		CGraphicsUtilities::RenderString(100, 0, "テレサ　スペースで攻撃、死亡");
		break;
	}
}

/*****************************************************************
 * @fn
 * デバッグ描画
 * @param なし
 * @return なし
 *****************************************************************/
void COnishi::RenderDebug() {
	
}

/*****************************************************************
 * @fn
 * 解放
 * @param なし
 * @return なし
 *****************************************************************/
void COnishi::Release() {

}