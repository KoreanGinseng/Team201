#pragma once
#include	"Mof.h"
#include	<unordered_map>
#include	"Effect.h"

constexpr	int		DefEffectPool = 10;		//! エフェクトプール数

//エフェクト管理クラス
class CEffectManager
{
private:
	std::unordered_map<std::string, CDynamicArray<CEffect*>>	m_Resource;			//! データ
	CEffectManager(void);
	~CEffectManager(void);
public:
	static CEffectManager* GetEffect(void);											//! マネージャー呼び出し
	static CEffect* GetEffect(const std::string& str);								//! 再生可能なエフェクト取得
	static void Start(const std::string& str, const Vector2& pos);					//! エフェクトの再生
	static void Start(const std::string& str, const float& x, const float& y);		//! エフェクトの再生
	static bool Load(const std::string& str);										//! 読込
	static void Update(void);														//! エフェクトの制御
	static void Render(void);														//! エフェクトの描画
	static void Release(void);														//! 解放
};

