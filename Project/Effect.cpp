#include		"Effect.h"

CEffect::CEffect() {


}

CEffect::~CEffect() {


}

void CEffect::Initialize(int type) {
	//座標の初期化
	m_Pos = Vector2(0, 0);
	//表示フラグの初期化
	m_bShow = false;
	//タイプによってアニメーションに入れる
	SpriteAnimationCreate* anim;
	anim = g_pAnimManager->GetResource(FileName[ANIMATION_EFFECT_EXPROSION + type])->GetAnim();
	int c = g_pAnimManager->GetResource(FileName[ANIMATION_EFFECT_EXPROSION + type])->GetAnimCount();
	m_Motion.Create(anim, c);
}

void CEffect::Start(float px, float py) {
	//エフェクトを呼び出された場合、引数からもらった座標に出現
	m_SrcRect = m_Motion.GetSrcRect();

	m_Pos.x = px - m_SrcRect.GetWidth()*0.5f;
	m_Pos.y = py - m_SrcRect.GetHeight()*0.5f;
	m_bShow = true;
	m_Motion.ChangeMotion(0);
}

void CEffect::Update(void) {
	//非表示の場合処理をしない
	if (!m_bShow)
	{
		return;
	}

	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();

	//エフェクトモーションが終了した場合、非表示にする
	if (m_Motion.IsEndMotion())
	{
		m_bShow = false;
	}

}

void CEffect::Render(const Vector2& screenPos) {
	//非表示の場合描画しない
	if (!m_bShow)
	{
		return;
	}

	//エフェクトの描画
	m_pTexture->Render(screenPos.x, screenPos.y,m_SrcRect);

}

void CEffect::Release(void) {
	//エフェクトモーションの解放
	m_Motion.Release();
}