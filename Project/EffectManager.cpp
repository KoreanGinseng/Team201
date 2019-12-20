#include		"EffectManager.h"

bool CEffectManager::Load() {

	//テクスチャの読み込み
	for (int i = 0; i < EFFECT_TYPECOUNT; i++)
	{
		m_Texture[i] = g_pTextureManager->GetResource(FileName[TEXTURE_EFFECT_EXPROSION + i]);
	}
	return true;
}

void CEffectManager::Initialize() {

	//エフェクトの基礎設定
	for (int j = 0; j < EFFECT_TYPECOUNT; j++)
	{
		for (int i = 0; i < EFFECTCOUNT; i++)
		{
			m_Effect[i][j].SetTexture(m_Texture[j]);
			m_Effect[i][j].Initialize(j);
		}
	}
}

CEffect* CEffectManager::Start(float px, float py, int type) {

	//エフェクトの情報を渡す
	for (int i = 0; i < EFFECTCOUNT; i++)
	{
		if (m_Effect[i][type].GetShow()) {

			continue;
		}
		m_Effect[i][type].Start(px, py);
		return &m_Effect[i][type];
	}
	return nullptr;
}

void CEffectManager::Update(void) {

	//エフェクトの更新
	for (int j = 0; j < EFFECT_TYPECOUNT; j++)
	{
		for (int i = 0; i < EFFECTCOUNT; i++)
		{
			m_Effect[i][j].Update();
		}
	}
}

void CEffectManager::Render(const Vector2& scroll) {

	//エフェクトの描画
	for (int j = 0; j < EFFECT_TYPECOUNT; j++)
	{
		for (int i = 0; i < EFFECTCOUNT; i++)
		{
			m_Effect[i][j].Render(scroll);
		}
	}
}


void CEffectManager::Release(void) {

	//エフェクトとテクスチャーの解放
	for (int j = 0; j < EFFECT_TYPECOUNT; j++)
	{
		for (int i = 0; i < EFFECTCOUNT; i++)
		{
			m_Effect[i][j].Release();
		}
	}
}