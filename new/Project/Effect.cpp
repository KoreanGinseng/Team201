#include		"Effect.h"

CEffect::CEffect() {


}

CEffect::~CEffect() {


}

void CEffect::Initialize(int type) {
	//���W�̏�����
	m_Pos = Vector2(0, 0);
	//�\���t���O�̏�����
	m_bShow = false;

	//�^�C�v�ɂ���ăA�j���[�V�����ɓ����
	switch (type)
	{
	
	case EFC_TEST:
	{
		SpriteAnimationCreate anim[] = {

			{

			"�e�X�g�G�t�F�N�g",
			0,0,
			120,120,
			FALSE,{{3,0,0},{3,1,0},{3,2,0},{3,3,0},{3,4,0}}

			},
		};

		m_Motion.Create(anim, 1);
		break;
	}

	}


}

void CEffect::Start(float px, float py) {
	//�G�t�F�N�g���Ăяo���ꂽ�ꍇ�A�����������������W�ɏo��
	m_SrcRect = m_Motion.GetSrcRect();

	m_Pos.x = px - m_SrcRect.GetWidth()*0.5f;
	m_Pos.y = py - m_SrcRect.GetHeight()*0.5f;
	m_bShow = true;
	m_Motion.ChangeMotion(0);
}

void CEffect::Update() {
	//��\���̏ꍇ���������Ȃ�
	if (!m_bShow)
	{
		return;
	}

	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();

	//�G�t�F�N�g���[�V�������I�������ꍇ�A��\���ɂ���
	if (m_Motion.IsEndMotion())
	{
		m_bShow = false;
	}

}

void CEffect::Render(Vector2 screenPos) {
	//��\���̏ꍇ�`�悵�Ȃ�
	if (!m_bShow)
	{
		return;
	}

	//�G�t�F�N�g�̕`��
	m_pTexture->Render(screenPos.x, screenPos.y,m_SrcRect);

}

void CEffect::Release() {
	//�G�t�F�N�g���[�V�����̉��
	m_Motion.Release();
}