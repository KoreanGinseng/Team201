/*****************************************************************
 *	@file			Fujiwara.cpp
 *	@brief			�t�W�����V�[������
 *	@author			����D�R
 *	@date			2019/07/29
 *****************************************************************/

//! INCLUDE
#include	"Fujiwara.h"


/*****************************************************************
 * @fn
 * �����Ȃ��R���X�g���N�^
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
CFujiwara::CFujiwara() :
CSceneBase() {
}

/*****************************************************************
 * @fn
 * �����Ȃ��f�X�g���N�^
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
CFujiwara::~CFujiwara() {
	Release();
}

/*****************************************************************
 * @fn
 * �K�v�ȑf�ނ̓ǂݍ���
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
bool CFujiwara::Load() {
	//���\�[�X�z�u�f�B���N�g���̐ݒ�
	CUtilities::SetCurrentDirectory("Resource");
	m_pFontTexture = new CTexture();
	m_pFontTexture->Load("sumple_imvisible.png");
	return TRUE;
}

/*****************************************************************
 * @fn
 * ������
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
void CFujiwara::Initialize() {
	X = 0;
	Y = 0;
	Lenth = 0;
	num = 0;
	
}

/*****************************************************************
 * @fn
 * �X�V
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
void CFujiwara::Update() {
	
	num += 1;

}

/*****************************************************************
 * @fn
 * �`��
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
void CFujiwara::Render() {
	//m_pFontTexture->RenderScale(0, 0, FONT_SIZE/64);
	
	String(0, 0, FONT_SIZE,num );
	

}

/*****************************************************************
 * @fn
 * �f�o�b�O�`��
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
void CFujiwara::RenderDebug() {

}

/*****************************************************************
 * @fn
 * ���
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
void CFujiwara::Release() {
	m_pFontTexture->Release();
	delete m_pFontTexture;
	m_pFontTexture = nullptr;
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
		m_pFontTexture->RenderScale(sx - size * fontsize, sy, fontsize / 64.0, SRect);//(�\�����W��,�\�����Wy,�g�嗦,rect)
	}
	
}

