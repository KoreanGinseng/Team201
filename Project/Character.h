#pragma once
#include "Object.h"

class CCharacter :
	public CObject
{
protected:
	Vector2						m_Move;				//移動量
	CSpriteMotionController*	m_pMotion;			//アニメーション
	RectArray					m_SrcRectArray;		//当たり判定用矩形
	bool						m_bDead;			//死亡フラグ
	bool						m_bReverse;			//反転フラグ
	int							m_DamageWait;		//ダメージ待ちフレーム
	bool						m_bCollision;		//当たり判定をするかどうかのフラグ
public:
	CCharacter(void);//コンストラクタ
	virtual ~CCharacter(void);//デストラクタ
	void Initialize(void) override = 0;				//初期化
	void Update(void) override = 0;					//更新
	void Render(const Vector2& screenPos) override;	//描画
	void Release(void) override;					//解放
	void LoadRect(const char* pName);				//当たり判定用矩形読み込み
	bool IsDead(void) const { return m_bDead; }		//死亡フラグ取得
	CRectangle GetSrcRect(void) const;				//アニメーション矩形取得
	virtual CRectangle GetRect(void) const;			//当たり判定用矩形取得
	RectArray GetSrcRectArray(void) const			//当たり判定用矩形の配列取得
	{ return m_SrcRectArray; }
	RectArray* GetSrcRectArrayPointer(void)			//当たり判定用矩形の配列をポインタで取得
	{ return &m_SrcRectArray; }
	RectArray GetRectArray(void) const;				//当たり判定用矩形の配列取得
	CRectangle GetRectArray(const int& n) const {	//当たり判定用矩形の配列を番号指定で取得
		return CRectangle(
			m_Pos.x + m_SrcRectArray[n].Left, m_Pos.y + m_SrcRectArray[n].Top,
			m_Pos.x + m_SrcRectArray[n].Right, m_Pos.y + m_SrcRectArray[n].Bottom);
	}
	int GetDamageWait(void) const					//ダメージ待ちフレーム取得
	{ return m_DamageWait; }
	virtual bool OverValue(CRectangle rec, Vector2& out);	//自身との埋まり値を計算して返す
	virtual void CollisionStage(const Vector2& over);		//埋まった時の処理
	void SetCollisionFlag(const bool& b)					//当たり判定をするかどうかのフラグ設定
	{ m_bCollision = b; }
	bool IsCollisionFlag(void) const						//当たり判定をするかどうかのフラグ取得
	{ return m_bCollision; }
	bool IsStageOver(void) const {							//ステージの範囲外に出ているかどうかを調べる
		return (GetRect().Right < CCordinate::GetStageRect().Left || m_Pos.x > CCordinate::GetStageRect().Right ||
			GetRect().Bottom < CCordinate::GetStageRect().Top || m_Pos.y > CCordinate::GetStageRect().Bottom);
	}
};

