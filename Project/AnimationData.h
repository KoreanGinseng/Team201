#pragma once
#include	"Mof.h"
#include	"TextureManager.h"

//アニメーションデータクラス
class CAnimationData
{
private:
	std::string				m_TextureName;		//! アニメーションデータの画像名
	SpriteAnimationCreate*	m_pAnim;			//! アニメーションデータ
	int						m_AnimCount;		//! アニメーション数
public:
	CAnimationData(void);						//! コンストラクタ
	~CAnimationData(void);						//! デストラクタ
	bool Load(const std::string& str);			//! 読込
	SpriteAnimationCreate* GetAnim(void);		//! アニメーションデータ取得
	int GetAnimCount(void) const;				//! アニメーション数取得
	std::string GetTextureName(void) const;		//! 画像名取得
	void Release(void);							//! 解放
};

