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
	SpriteAnimationCreate* anim;
	anim = g_pAnimManager->GetResource(FileName[ANIMATION_EFFECT_EXPROSION + type])->GetAnim();
	int c = g_pAnimManager->GetResource(FileName[ANIMATION_EFFECT_EXPROSION + type])->GetAnimCount();
	m_Motion.Create(anim, c);
}

void CEffect::Start(float px, float py) {
	//�G�t�F�N�g���Ăяo���ꂽ�ꍇ�A�����������������W�ɏo��
	m_SrcRect = m_Motion.GetSrcRect();

	m_Pos.x = px - m_SrcRect.GetWidth()*0.5f;
	m_Pos.y = py - m_SrcRect.GetHeight()*0.5f;
	m_bShow = true;
	m_Motion.ChangeMotion(0);
}

void CEffect::Update(void) {
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

void CEffect::Render(const Vector2& screenPos) {
	//��\���̏ꍇ�`�悵�Ȃ�
	if (!m_bShow)
	{
		return;
	}

	//�G�t�F�N�g�̕`��
	m_pTexture->Render(screenPos.x, screenPos.y,m_SrcRect);

}

void CEffect::Release(void) {
	//�G�t�F�N�g���[�V�����̉��
	m_Motion.Release();
}