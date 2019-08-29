/*****************************************************************
 *	@file			Inoue.cpp
 *	@brief			�C�m�E�G�V�[������
 *	@author			����D�R
 *	@date			2019/07/29
 *****************************************************************/

//! INCLUDE
#include	"Inoue.h"

extern char*		g_StageFileName[STAGECOUNT];

/*****************************************************************
 * @fn
 * �����Ȃ��R���X�g���N�^
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
CInoue::CInoue() :
CSceneBase() {
}

/*****************************************************************
 * @fn
 * �����Ȃ��f�X�g���N�^
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
CInoue::~CInoue() {
	Release();
}

/*****************************************************************
 * @fn
 * �K�v�ȑf�ނ̓ǂݍ���
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
void CInoue::Load() {
	for (int i = 0; i < STAGECOUNT; i++) {
		m_Stage[i].Load(g_StageFileName[i]);
	}
	m_Player1.Load("Player.png");
	m_Player2.Load("Player2.png");
}

/*****************************************************************
 * @fn
 * ������
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
void CInoue::Initialize() {
	m_Pos = Vector2(0, 0);
	for (int i = 0; i < STAGECOUNT; i++) {
		m_Stage[i].Initialize();
	}
	m_StageNo = 0;
}

/*****************************************************************
 * @fn
 * �X�V
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
void CInoue::Update() {
	g_pInput->GetMousePos(m_MousePos);

	Vector2 move = Vector2(0, 0);

	if (g_pInput->IsKeyHold(MOFKEY_LEFT)) {
		//move.x -= MOVESPEED;
		move.x += MOVESPEED;
	}
	if (g_pInput->IsKeyHold(MOFKEY_UP)) {
		move.y += MOVESPEED;
	}
	if (g_pInput->IsKeyHold(MOFKEY_RIGHT)) {
		//move.x += MOVESPEED;
		move.x -= MOVESPEED;
	}
	if (g_pInput->IsKeyHold(MOFKEY_DOWN)) {
		move.y -= MOVESPEED;
	}

	m_Pos += move;

	if (m_Pos != m_MainCamera.GetScroll()) {
		Vector2 d = m_Pos - m_MainCamera.GetScroll();
		d /= MOVESPEED*0.5;
		m_MainCamera.AddScroll(d);
	}

	if (g_pInput->IsKeyPush(MOFKEY_ESCAPE)) {
		PostQuitMessage(0);
	}

	/*if (g_pInput->IsKeyHold(MOFKEY_A)) {
		m_MainCamera.AddScroll(Vector2(-MOVESPEED, 0));
	}
	if (g_pInput->IsKeyHold(MOFKEY_W)) {
		m_MainCamera.AddScroll(Vector2( 0, MOVESPEED));
	}
	if (g_pInput->IsKeyHold(MOFKEY_D)) {
		m_MainCamera.AddScroll(Vector2(MOVESPEED, 0));
	}
	if (g_pInput->IsKeyHold(MOFKEY_S)) {
		m_MainCamera.AddScroll(Vector2(0, -MOVESPEED));
	}*/

	if (g_pInput->IsKeyPush(MOFKEY_O)) {
		m_StageNo++;
		if (m_StageNo >= STAGECOUNT) {
			m_StageNo = 0;
		}
	}

	m_Stage[m_StageNo].Update();

	if (g_pInput->IsKeyPush(MOFKEY_SPACE)) {
		g_pGraphics->ChangeScreenMode();
	}
}

/*****************************************************************
 * @fn
 * �`��
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
void CInoue::Render() {

	m_Stage[m_StageNo].Render(m_MainCamera.GetScroll());


	Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_Pos);
	if (m_StageNo == 0) {
		m_Player1.Render(screenPos.x, screenPos.y);
	}
	else {
		m_Player2.Render(screenPos.x, screenPos.y);
	}
	CGraphicsUtilities::RenderFillRect(screenPos.x, screenPos.y, screenPos.x + RECTSIZE, screenPos.y + RECTSIZE, MOF_COLOR_GREEN);
}

/*****************************************************************
 * @fn
 * �f�o�b�O�`��
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
void CInoue::RenderDebug() {

	m_Stage[m_StageNo].RenderDebug(m_MainCamera.GetScroll());
	

	Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_Pos);
	CGraphicsUtilities::RenderString(10, 10, "camera[x]:%5.1f [y]:%5.1f", m_MainCamera.GetScroll().x, m_MainCamera.GetScroll().y);
	CGraphicsUtilities::RenderString(10, 30, "world [x]:%5.1f [y]:%5.1f", m_Pos.x, m_Pos.y);
	CGraphicsUtilities::RenderString(10, 50, "screen[x]:%5.1f [y]:%5.1f", screenPos.x, screenPos.y);
}

/*****************************************************************
 * @fn
 * ���
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
void CInoue::Release() {
	for (int i = 0; i < STAGECOUNT; i++) {
		m_Stage[i].Release();
	}
}