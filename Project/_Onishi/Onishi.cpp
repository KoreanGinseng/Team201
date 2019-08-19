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
		}
		else if (g_pInput->IsKeyHold(MOFKEY_RIGHT))
		{
			Xpos += spead;
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
}

/*****************************************************************
 * @fn
 * �`��
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
void COnishi::Render() {
	float x = (MXpos - Xpos);
	float y = (MYpos - Ypos);

	float tx = sqrtf(x*x);
	float ty = sqrtf(y*y);

	float c = sqrtf(x * x + y * y);

	float cx = c / x;
	float cy = c / y;

	CGraphicsUtilities::RenderString(0, 0,MOF_COLOR_BLACK, "�����n���T�C�R�[?.%.1f",time);
	CGraphicsUtilities::RenderCircle(Xpos, Ypos,10,MOF_COLOR_BLACK);
	if (atack) {
		//CGraphicsUtilities::RenderLine(Xpos, Ypos, MXpos, MYpos, MOF_COLOR_WHITE);
		if (MXpos>=Xpos&&MYpos>=Ypos) {
			CGraphicsUtilities::RenderLine(Xpos, Ypos, tx * 1000, ty * 1000, MOF_COLOR_WHITE);
		}
		else if (MXpos<=Xpos&& MYpos > Ypos) {
			CGraphicsUtilities::RenderLine(Xpos, Ypos, -tx * 1000, ty * 1000, MOF_COLOR_WHITE);
		}else if (MXpos <= Xpos && MYpos <= Ypos) {
			CGraphicsUtilities::RenderLine(Xpos, Ypos, -tx * 1000, -ty * 1000, MOF_COLOR_WHITE);
		}else if (MXpos >= Xpos && MYpos < Ypos) {
			CGraphicsUtilities::RenderLine(Xpos, Ypos, tx * 1000, -ty * 1000, MOF_COLOR_WHITE);
		}

	}
	if (poase) {
		CGraphicsUtilities::RenderFillRect(g_pGraphics->GetTargetWidth() / 4, g_pGraphics->GetTargetHeight() / 3, 700, 600, MOF_COLOR_WHITE);
	}
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

}