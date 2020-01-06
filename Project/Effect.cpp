#include "Effect.h"



CEffect::CEffect(void) :
m_pTexture(nullptr),
m_Motion(),
m_bShow(false),
m_Pos(Vector2(0, 0))
{
}


CEffect::~CEffect(void)
{
}

bool CEffect::IsShow(void) const
{
	return m_bShow;
}

void CEffect::Start(const Vector2 & pos)
{
	//発生位置に座標セット
	m_Pos = pos;
	//表示フラグON
	m_bShow = true;
	//アニメーションを先頭にセットする
	m_Motion.SetTime(0);
}

bool CEffect::Load(const std::string& str)
{
	//データが存在しない場合読み込み
	if (CAnimationManager::GetAnimation(str) == nullptr)
	{
		CAnimationManager::Load(str);
	}
	CAnimationData* pData = CAnimationManager::GetAnimation(str);
	//データが正しく読み込めていない場合失敗
	if (pData == nullptr)
	{
		return false;
	}
	//画像が存在しない場合読み込み
	std::string texName = pData->GetTextureName();
	if (CTextureManager::GetTexture(texName) == nullptr)
	{
		CTextureManager::Load(texName.c_str());
	}
	m_pTexture = CTextureManager::GetTexture(texName);
	//画像が正しく読み込めていない場合失敗
	if (m_pTexture == nullptr)
	{
		return false;
	}
	//モーションの作成
	int animCount = pData->GetAnimCount();
	SpriteAnimationCreate* pAnim = pData->GetAnim();
	m_Motion.Create(pAnim, animCount);
	return true;
}

void CEffect::Update(void)
{
	//表示フラグが立っていない場合スキップ
	if (!m_bShow)
	{
		return;
	}
	//アニメーションを更新
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	//アニメーションが終了していればフラグを折る
	if (m_Motion.IsEndMotion())
	{
		m_bShow = false;
	}
}

void CEffect::Render(void)
{
	//表示フラグが立っていない場合スキップ
	if (!m_bShow)
	{
		return;
	}
	m_pTexture->Render(m_Pos.x, m_Pos.y, m_Motion.GetSrcRect());
}

void CEffect::Release(void)
{
	m_pTexture = nullptr;
	m_Motion.Release();
}
