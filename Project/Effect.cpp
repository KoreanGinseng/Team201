#include		"Effect.h"

CEffect::CEffect() {


}

CEffect::~CEffect() {


}

void CEffect::Initialize(int type) {
	//座標の初期化
	m_PosX = 0.0f;
	m_PosY = 0.0f;
	//表示フラグの初期化
	m_bShow = false;

	//タイプによってアニメーションに入れる
	switch (type)
	{
	
	case EFC_TEST: {

		SpriteAnimationCreate anim[] = {

			{

			"テストエフェクト",
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
	//エフェクトを呼び出された場合、引数からもらった座標に出現
	m_SrcRect = m_Motion.GetSrcRect();

	m_PosX = px - m_SrcRect.GetWidth()*0.5f;
	m_PosY = py - m_SrcRect.GetHeight()*0.5f;
	m_bShow = true;
	m_Motion.ChangeMotion(0);
}

void CEffect::Update() {
	//非表示の場合処理をしない
	if (!m_bShow) {

		return;

	}

	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();

	//エフェクトモーションが終了した場合、非表示にする
	if (m_Motion.IsEndMotion()) {

		m_bShow = false;
		

	}

}

void CEffect::Render(Vector2 scroll) {
	//非表示の場合描画しない
	if (!m_bShow) {

		return;

	}

	//エフェクトの描画
	m_pTexture->Render(scroll.x, scroll.y,m_SrcRect);

}

void CEffect::Release() {

	//エフェクトモーションの解放
	m_Motion.Release();

}