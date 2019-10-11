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
	gEnemytype = ENEMY_KOTEIHOUDAI;//デバック
	switch (gEnemytype)
	{
	case ENEMY_KURIBO:
		gEnemy = new CEnemy_KURIBO();
		gAtack = new CAtack_KURIBO();
		break;
	case ENEMY_NOKONOKO:
		gEnemy = new CENEMY_NOKONOKO();
		gAtack = new CAtack_NOKONOKO();
		break;
	case ENEMY_TERESA:
		gEnemy = new CENEMY_TERESA();
		gAtack = new CAtack_TERESA();
		break;
	case ENEMY_BAT:
		gEnemy = new CENEMY_BAT();
		gAtack = new CAtack_BAT();
		break;
	case ENEMY_KOTEIHOUDAI:
		gEnemy = new CENEMY_KOTEIHOUDAI();
		gAtack = new CAtack_KOTEIHOUDAI();
		break;
	}

	gEnemy->Initialize();
	gAtack->Initialize();
	//gEnemy.Initialize(gEnemytype);
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

		gEnemy->Release();

		if (gEnemytype == ENEMY_KURIBO) {
			gEnemytype = ENEMY_NOKONOKO;
			gEnemy = new CENEMY_NOKONOKO();
			gAtack = new CAtack_NOKONOKO();
		}
		else if (gEnemytype == ENEMY_NOKONOKO) {
			gEnemytype = ENEMY_TERESA;
			gEnemy = new CENEMY_TERESA();
			gAtack = new CAtack_TERESA();
		}
		else if (gEnemytype == ENEMY_TERESA) {
			gEnemytype = ENEMY_BAT;
			gEnemy = new CENEMY_BAT();
			gAtack = new CAtack_BAT();
		}
		else if (gEnemytype == ENEMY_BAT) {
			gEnemytype = ENEMY_KOTEIHOUDAI;
			gEnemy = new CENEMY_KOTEIHOUDAI();
			gAtack = new CAtack_KOTEIHOUDAI();
		}
		else
		{
			gEnemytype = ENEMY_KURIBO;
			gEnemy = new CEnemy_KURIBO();
			gAtack = new CAtack_KURIBO();
		}
			gEnemy->Initialize();
	}


	gEnemy->Update(Xpos, Ypos);
	gAtack->Update(gEnemy->GetXpos(), gEnemy->GetYpos(), gEnemy->getRevers(), Xpos, Ypos);
	//gEnemy.Update(Xpos, Ypos, gEnemytype);
	float ox = 0, oy = 0;
	float mx = gEnemy->GetXpos(), my = gEnemy->GetYpos();
	if (mx < 200) {
		ox = 200 - mx;
	}
	else if (mx > 800)
	{
		ox = 800 - mx;

	}
	if (my > 600) {
		oy = 600 - my;
	}
	gEnemy->CollisionStage(ox, oy, gEnemytype);
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

	if (MXpos <= Xpos) {
		tx = -tx;
	}

	if (MYpos <= Ypos) {
		ty = -ty;
	}

	/*float a = tx / ty;
	float ax = MYpos/a;
	float ay = a*MXpos;
	

	float c = sqrtf(x * x + y * y);

	float cx = x / c;
	float cy = y / c;*/
	
	


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

	gEnemy->Render(Xpos,Ypos);
	gAtack->Render();
	//gEnemy.Render(Xpos, Ypos,gEnemytype);

	switch (gEnemytype)
	{
	case ENEMY_KURIBO:
		CGraphicsUtilities::RenderString(100, 0, "クリボー");
		break;
	case ENEMY_NOKONOKO:
		CGraphicsUtilities::RenderString(100, 0, "ノコノコ");
		break;
	case ENEMY_TERESA:
		CGraphicsUtilities::RenderString(100, 0, "テレサ");
		break;
	case ENEMY_BAT:
		CGraphicsUtilities::RenderString(100, 0, "蝙蝠");
		break;
	case ENEMY_KOTEIHOUDAI:
		CGraphicsUtilities::RenderString(100, 0, "固定砲台");
		break;
	}
	CGraphicsUtilities::RenderLine(0, 600, g_pGraphics->GetTargetWidth(), 600, MOF_COLOR_WHITE);
	CGraphicsUtilities::RenderLine(200, 0, 200, g_pGraphics->GetTargetHeight(), MOF_COLOR_WHITE);
	CGraphicsUtilities::RenderLine(800, 0, 800, g_pGraphics->GetTargetHeight(), MOF_COLOR_WHITE);

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
	if (gEnemy) {
		gEnemy->Release();
		delete gEnemy;
		gEnemy = NULL;
	}
	if (gAtack) {
		gAtack->Release();
		delete gAtack;
		gAtack = NULL;
	}
	
}