#include		"EffectManager.h"

CEffectManager::CEffectManager() {


}
CEffectManager::~CEffectManager() {


}

bool CEffectManager::Load() {

	//テクスチャの読み込み
	char* name[] = {

		"Effect.png"
	};

	for (int i = 0; i < EFC_TYPECOUNT; i++) {

		if (!m_Texture[i].Load(name[i])) {

			return false;

		}
	}

	return true;

}

void CEffectManager::Initialize() {

	//エフェクトの基礎設定
	for (int j = 0; j < EFC_TYPECOUNT; j++)
	{
		for (int i = 0; i < EFFECTCOUNT; i++)
		{
			m_Effect[i][j].SetTexture(&m_Texture[j]);
			m_Effect[i][j].Initialize(j);
		}
	}


}

CEffect* CEffectManager::Start(float px, float py, int type) {

	//エフェクトの情報を渡す
	for (int i = 0; i < EFFECTCOUNT; i++) {

		if (m_Effect[i][type].GetShow()) {

			continue;
		}

		m_Effect[i][type].Start(px, py);
		return &m_Effect[i][type];

	}

	return NULL;

}

void CEffectManager::Update(void) {

	//エフェクトの更新
	for (int j = 0; j < EFC_TYPECOUNT; j++) {

		for (int i = 0; i < EFFECTCOUNT; i++) {

			m_Effect[i][j].Update();

		}
	}
}

void CEffectManager::Render(Vector2 scroll) {

	//エフェクトの描画
	for (int j = 0; j < EFC_TYPECOUNT; j++)
	{
		for (int i = 0; i < EFFECTCOUNT; i++)
		{
			m_Effect[i][j].Render(scroll);
		}
	}
}


void CEffectManager::Release(void) {

	//エフェクトとテクスチャーの解放
	for (int j = 0; j < EFC_TYPECOUNT; j++)
	{
		for (int i = 0; i < EFFECTCOUNT; i++)
		{
			m_Effect[i][j].Release();
		}
		m_Texture[j].Release();
	}

}