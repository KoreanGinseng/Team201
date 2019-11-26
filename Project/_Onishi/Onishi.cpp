/*****************************************************************
 *	@file			Onishi.cpp
 *	@brief			�I�I�j�V�V�[������
 *	@author			����D�R
 *	@date			2019/07/29
 *****************************************************************/

//! INCLUDE
#include	"Onishi.h"

/*****************************************************************
 * @fn
 * �����Ȃ��R���X�g���N�^
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
COnishi::COnishi() :
CSceneBase() {
}

/*****************************************************************
 * @fn
 * �����Ȃ��f�X�g���N�^
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
COnishi::~COnishi() {
	Release();
}

/*****************************************************************
 * @fn
 * �K�v�ȑf�ނ̓ǂݍ���
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
void COnishi::Load() {

}

/*****************************************************************
 * @fn
 * ������
 * @param �Ȃ�
 * @return �Ȃ�
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
	gEnemytype = ENEMY_TESTBOS3;//�f�o�b�N
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
	case ENEMY_TESTBOS:
		gEnemy = new CEnemy_TESTBOS();
		gAtack = new CAtack_TESTBOS();
		break;
	case ENEMY_FLOATING:
		gEnemy = new CENEMY_FLOATING();
		gAtack = new CAtack_TERESA();
		break;
	case ENEMY_POISONKURIBO:
		gEnemy = new CEnemy_POISONKURIBO();
		gAtack = new CAtack_POISONKURIBO();
		break;
	case ENEMY_TESTBOS2:
		gEnemy = new CEnemy_TESTBOS2();
		gAtack = new CAtack_TESTBOS2();
		break;
	case ENEMY_TESTBOS3:
		gEnemy = new CEnemy_TESTBOS3();
		gAtack = new CAtack_TESTBOS3();
		break;
	/*case ENEMY_RIGHTHAND:
		gEnemy = new CEnemy_RIGHTHAND();
		gAtack = new CAtack_RIGHTHAND();
		break;*/
	}

	gEnemy->Initialize();
	gAtack->Initialize();
}

/*****************************************************************
 * @fn
 * �X�V
 * @param �Ȃ�
 * @return �Ȃ�
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
	
	
	time += 1 * CUtilities::GetFrameSecond();

	if (g_pInput->IsKeyPush(MOFKEY_RETURN)) {

		gEnemy->Release();
		delete gEnemy;
		gAtack->Release();
		delete gAtack;
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
		else if (gEnemytype == ENEMY_KOTEIHOUDAI) {
			gEnemytype = ENEMY_TESTBOS;
			gEnemy = new CEnemy_TESTBOS();
			gAtack = new CAtack_TESTBOS();
		}
		else if (gEnemytype == ENEMY_TESTBOS) {
			gEnemytype = ENEMY_FLOATING;
			gEnemy = new CENEMY_FLOATING();
			gAtack = new CAtack_TERESA();
		}
		else if (gEnemytype == ENEMY_FLOATING) {
			gEnemytype = ENEMY_POISONKURIBO;
			gEnemy = new CEnemy_POISONKURIBO();
			gAtack = new CAtack_POISONKURIBO();
		}
		else if (gEnemytype == ENEMY_POISONKURIBO) {
			gEnemytype = ENEMY_TESTBOS2;
			gEnemy = new CEnemy_TESTBOS2();
			gAtack = new CAtack_TESTBOS2();
		}
		else if (gEnemytype == ENEMY_TESTBOS2) {
			gEnemytype = ENEMY_TESTBOS3;
			gEnemy = new CEnemy_TESTBOS3();
			gAtack = new CAtack_TESTBOS3();
		}
		/*else if (gEnemytype == ENEMY_TESTBOS3) {
			gEnemytype = ENEMY_RIGHTHAND;
			gEnemy = new CEnemy_RIGHTHAND();
			gAtack = new CAtack_RIGHTHAND();
		}*/
		else
		{
			gEnemytype = ENEMY_KURIBO;
			gEnemy = new CEnemy_KURIBO();
			gAtack = new CAtack_KURIBO();
		}
			gEnemy->Initialize();
			gAtack->Initialize();
	}


	gEnemy->Update(Xpos, Ypos);
	if (!gEnemy->GetDead()) {
	gAtack->Update(gEnemy->GetXpos(), gEnemy->GetYpos(), gEnemy->getRevers(), Xpos, Ypos);

	}
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
 * �`��
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
void COnishi::Render() {
	
	


	CGraphicsUtilities::RenderString(g_pGraphics->GetTargetWidth()/4*3,0,MOF_COLOR_BLACK, "�^�C���F%.1f",time);
	CGraphicsUtilities::RenderFillCircle(Xpos, Ypos, 10, MOF_COLOR_BLACK);
	
	if (h) {
		CGraphicsUtilities::RenderFillCircle(Xpos+getx,Ypos+gety, 30, MOF_COLOR_GREEN);
		
	}
	
	if (poase) {
		CGraphicsUtilities::RenderFillRect(g_pGraphics->GetTargetWidth() / 4, g_pGraphics->GetTargetHeight() / 3, 700, 600, MOF_COLOR_WHITE);
	}

	gEnemy->Render(Xpos,Ypos);
	gAtack->Render();

	switch (gEnemytype)
	{
	case ENEMY_KURIBO:
		CGraphicsUtilities::RenderString(100, 0, "�N���{�[");
		break;
	case ENEMY_NOKONOKO:
		CGraphicsUtilities::RenderString(100, 0, "�m�R�m�R");
		break;
	case ENEMY_TERESA:
		CGraphicsUtilities::RenderString(100, 0, "�e���T");
		break;
	case ENEMY_BAT:
		CGraphicsUtilities::RenderString(100, 0, "��");
		break;
	case ENEMY_KOTEIHOUDAI:
		CGraphicsUtilities::RenderString(100, 0, "�Œ�C��");
		break;
	case ENEMY_TESTBOS:
		CGraphicsUtilities::RenderString(100, 0, "�����̃{�X");
		break;
	case ENEMY_FLOATING:
		CGraphicsUtilities::RenderString(100, 0, "�Y���G");
		break;
	case ENEMY_POISONKURIBO:
		CGraphicsUtilities::RenderString(100, 0, "�ŃN���{�[");
		break;
	case ENEMY_TESTBOS2:
		CGraphicsUtilities::RenderString(100, 0, "�X���̃{�X");
		break;
	case ENEMY_TESTBOS3:
		CGraphicsUtilities::RenderString(100, 0, "�Ō�̃{�X");
		break;
	case ENEMY_RIGHTHAND:
		CGraphicsUtilities::RenderString(100, 0, "�{�X�̉E��");
		break;
	}
	CGraphicsUtilities::RenderLine(0, 600, g_pGraphics->GetTargetWidth(), 600, MOF_COLOR_WHITE);
	CGraphicsUtilities::RenderLine(200, 0, 200, g_pGraphics->GetTargetHeight(), MOF_COLOR_WHITE);
	CGraphicsUtilities::RenderLine(800, 0, 800, g_pGraphics->GetTargetHeight(), MOF_COLOR_WHITE);
}

/*****************************************************************
 * @fn
 * �f�o�b�O�`��
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
void COnishi::RenderDebug() {
	
}

/*****************************************************************
 * @fn
 * ���
 * @param �Ȃ�
 * @return �Ȃ�
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