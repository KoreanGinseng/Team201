#pragma once
#include	"Mof.h"
#include	"AnimationData.h"
#include	<unordered_map>

//アニメーション管理クラス
class CAnimationManager
{
private:
	std::unordered_map<std::string, CAnimationData*> m_Resource;	//! データ
	CAnimationManager(void);
	~CAnimationManager(void);
public:
	static CAnimationManager* GetAnimation(void);					//! マネージャー呼び出し
	static CAnimationData* GetAnimation(const std::string& str);	//! アニメーションデータ取得
	static bool Load(const std::string& str);						//! ファイル名からデータ読み込み
	static void Release(void);										//! 解放
};

