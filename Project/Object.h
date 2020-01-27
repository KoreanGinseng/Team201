#pragma once
#include	"GameDefine.h"

class CObject
{
protected:
	Vector2			m_Pos;			//座標
	CTexturePtr		m_pTexture;		//画像ポインタ
	bool			m_bShow;		//表示フラグ
public:
	CObject();																//コンストラクタ
	virtual ~CObject();														//デストラクタ
	virtual void Initialize(void) = 0;										//初期化
	virtual void Update(void) = 0;											//更新
	virtual void Render(const Vector2& screenPos) = 0;						//描画
	virtual void Release(void) = 0;											//解放
	void SetPos(const float& x, const float& y) { SetPos(Vector2(x,y)); }	//座標設定
	void SetPos(const Vector2& pos) { m_Pos = pos; }						//座標設定
	virtual void SetTexture(const CTexturePtr& pt) { m_pTexture = pt; }		//画像設定
	void SetShow(const bool& b) { m_bShow = b; }							//表示フラグ変更
	bool IsShow(void) const { return m_bShow; }								//表示フラグ取得
	Vector2 GetPos(void) const { return m_Pos; }							//座標取得
};

