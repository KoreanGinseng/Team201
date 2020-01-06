#pragma once
#include	"Mof.h"
#include	<unordered_map>
#include	"Sound.h"

constexpr	int		DefSoundPool = 10;			//! 再生プール数

//サウンドエフェクト管理クラス
class CSoundManager
{
private:
	std::unordered_map<std::string, CDynamicArray<CSound*>> m_Resource;	//! データ
	CSoundManager(void);
	~CSoundManager(void);
public:
	static CSoundManager* GetSound(void);								//! マネージャー呼び出し 
	static CSound* GetSound(const std::string& str);					//! 再生可能なサウンド取得
	static CSoundBuffer* GetSoundBuffer(const std::string& str);		//! 再生可能なサウンド取得
	static void Play(const std::string& str);							//! 再生
	static void SetVolume(const std::string& str, const float& vol);	//! 音量の調節 vol(0.0f ~ 1.0f)
	static bool Load(const std::string& str);							//! 読込
	static void Update(void);											//! サウンド制御
	static void Release(void);											//! 解放
};

