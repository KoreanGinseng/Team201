#include	"Ranking.h"
#include	"VirtualKeyBoard.h"

unsigned short int KeyBoard[4][10] = {
	VK_1,VK_2,VK_3,VK_4,VK_5,VK_6,VK_7,VK_8,VK_9,VK_0,
	VK_Q,VK_W,VK_E,VK_R,VK_T,VK_Y,VK_U,VK_I,VK_O,VK_P,
	VK_A,VK_S,VK_D,VK_F,VK_G,VK_H,VK_J,VK_K,VK_L,VK_OEM_PLUS,
	VK_Z,VK_X,VK_C,VK_V,VK_B,VK_N,VK_M,VK_OEM_COMMA,VK_OEM_PERIOD,VK_OEM_2
};

CRanking::CRanking() :
m_bInit(false){
}

bool CRanking::Load() {

	m_pTexture = g_pTextureManager->GetResource(FileName[TEXTURE_FONT]);
	return TRUE;
}

void CRanking::Initialize() {
	
	m_bPadInputMode = false;
	m_PosCircle.x = g_pGraphics->GetTargetWidth()*0.5f;
	m_PosCircle.y = g_pGraphics->GetTargetHeight()*0.5f;
	m_PosCircle.r = 2.0f;
	m_KeyOffSet .x = (g_pGraphics->GetTargetWidth() - 64*10) * 0.5f;
	m_KeyOffSet.y = (g_pGraphics->GetTargetHeight() - 64*4) * 0.5f;
}

void CRanking::Update() {

	if (g_pInput->GetGamePadCount()) {

		PadOperation();
	}
	//���݂̃}�E�X���W���擾
	g_pInput->GetMousePos(m_MousePos);

	if (!m_bInit)
	{
		ImeInit();
		m_bInit = true;
	}

	//Ime�֘A�X�V
	ImeUpdate();
}

void CRanking::Render() {
	//Ime�֘A�`��
	ImeRender();
	
	for (int i = 0; i < m_RankingEntryArray.GetArrayCount(); i++) {
		CGraphicsUtilities::RenderString(10, 100 + i * 50, "%s", m_RankingEntryArray[i]->Name.GetString());
	}
	CGraphicsUtilities::RenderString(0, 100, "%d", m_bPadInputMode);
	KeyRender();

}

void CRanking::RenderDebug() {
	//CGraphicsUtilities::RenderString(10, 200, "%c", 0x7e);
	CGraphicsUtilities::RenderCircle(m_PosCircle, MOF_XRGB(255, 0, 0));
	
}

void CRanking::Release() {

}

void CRanking::ImeInit()
{
	//���͂��󂯕t���Ȃ�
	//g_pImeInput->SetEnable(FALSE);
	CImeProc::GetImeInput()->SetEnable(FALSE);
	m_bInputEnable = false;
	//���͒��������������
	g_pImeInput->SetInputString("");
	//���͊m�蕶������i�[
	m_String = "";
	m_VisibleCount = 0;
	m_InputCount = 0;
	//�t�H���g�̐���
	m_NameFont.Create(IME_FONT_SIZE, "�l�r�@����");
}

void CRanking::ImeUpdate() {
	//�_�ŗp�J�E���g�����Z
	m_VisibleCount++;
	if (m_VisibleCount > CUtilities::GetFPS()) {
		m_VisibleCount = 0;
	}
	
	//�e�L�X�g�{�b�N�X���N���b�N���ē��͂��J�n
	if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
	{
		if (GetTextBoxRect().CollisionPoint(m_MousePos))
		{
			g_pImeInput->SetEnable(TRUE);
			m_bInputEnable = true;
		}

		//���͊m�蕶�������͒��ɕϊ�
		g_pImeInput->SetInputString(m_String);
		m_String = "";

	}
	

	//�G���^�[�L�[�����������ɓ��͒������������
	if (g_pImeInput->GetEnterString()->GetLength() > 0)
	{
		//�o�^���閼�O�͂���ł�낵��
		//

		//���͊m�蕶����Ƃ��Ēǉ�
		m_String += g_pImeInput->GetEnterString()->GetString();

		//���͂��ꂽ�l��ۑ�
		RankingEntry* re = new RankingEntry;
		re->Name = m_String;
		re->IconRect = CRectangle(0, 0, 0, 0);
		re->Score = 0;
		m_RankingEntryArray.Add(&re);
		delete re;
		re = nullptr;
		//�ǉ���������͒������񃊃Z�b�g
		g_pImeInput->ResetEnterString();
		//���͂𖳌��ɂ���
		g_pImeInput->SetEnable(FALSE);
		m_bInputEnable = false;
	}
}

void CRanking::ImeRender() {
	//�e�L�X�g�{�b�N�X�̕`��
	CGraphicsUtilities::RenderFillRect(GetTextBoxRect(), MOF_COLOR_WHITE);
	//���͊m�蕶�����\��
	m_NameFont.RenderString(GetTextBoxRect().Left, GetTextBoxRect().Top, MOF_COLOR_RED, m_String.GetString());

	//���͊m�蕶���̋�`���擾
	CRectangle or;
	m_NameFont.CalculateStringRect(GetTextBoxRect().Left, GetTextBoxRect().Top, m_String.GetString(), or);

	//���͒��������\��(���͊m�蕶���̉E�ɕ��ׂĕ`��)
	CString it;
	g_pImeInput->GetInputImeString(it);
	m_NameFont.RenderString(or.Right, or.Top, MOF_COLOR_BLACK, it.GetString());

	//���͒������̋�`���擾
	CRectangle ir(GetTextBoxRect().Left, GetTextBoxRect().Top, GetTextBoxRect().Left + 2, GetTextBoxRect().Top + IME_FONT_SIZE - 2);
	if (it.GetLength() > 0) {
		m_NameFont.CalculateStringRect(GetTextBoxRect().Left, GetTextBoxRect().Top, it.GetString(), ir);
	}

	//�J�[�\���`��
	if (((int)m_VisibleCount) >= CUtilities::GetFPS() / 2.0f && m_bInputEnable) {
		CGraphicsUtilities::RenderLine(ir.Right + 2, ir.Top + 2, ir.Right + 2, ir.Bottom, MOF_COLOR_BLACK);
	}
}

void CRanking::KeyRender() {

	if (!m_bPadInputMode) {

		return;

	}

	for (int y = 0; y < 4; y++) {

		for (int x = 0; x < 10; x++) {

			String((m_KeyOffSet.x)+x*64, (m_KeyOffSet.y)+y*64, FONT_SIZE, KeyBoard[y][x]);
		}
	}

	RenderDebug();

	
}

void CRanking::SendKeyBoard(int y, int x) {
	keybd_event(KeyBoard[y][x], (BYTE)MapVirtualKey(KeyBoard[y][x], 0), 0, 0);
	keybd_event(KeyBoard[y][x], (BYTE)MapVirtualKey(KeyBoard[y][x], 0), KEYEVENTF_KEYUP, 0);
}

void CRanking::PadOperation() {

	
	//MOF_PRINTLOG("V%f H%f\n", g_pGamePad->GetStickVertical(), g_pGamePad->GetStickHorizontal());
	//MOF_PRINTLOG("%f\n", g_pGamePad->GetPadState()->lZ);

	if (g_pGamePad->IsKeyPush(GAMEKEY_RB)) {

		g_pImeInput->SetEnable(TRUE);
		m_bPadInputMode = true;
	}

	if (g_pGamePad->GetPadState()->lZ < -500.0f) {

		m_bPadInputMode = false;

	}

	if (!m_bPadInputMode) {

		return;

	}

	if (g_pGamePad->GetStickHorizontal() <= 0.04f&&g_pGamePad->GetStickHorizontal() >= -0.04f ||
		g_pGamePad->GetStickVertical() <= 0.04f&&g_pGamePad->GetStickVertical() >= -0.04f) {

		return;

	}

	 
	m_PosCircle.x += g_pGamePad->GetStickHorizontal()*2;
	m_PosCircle.y += g_pGamePad->GetStickVertical()*2;

	/*if (CollisionRectCircle()) {


	}*/

	
	
}