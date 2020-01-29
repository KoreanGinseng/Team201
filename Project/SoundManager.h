#pragma once
#include	"Mof.h"
#include	<unordered_map>
#include	"Sound.h"

constexpr	int		DefSoundPool = 10;			//! 再生プール数

//サウンドエフェクト管理クラス
class CSoundManager
{
private:
	std::unordered_map<std::string, CDynamicArray<CSound*>> m_ResourceSE;	//! データ
	std::unordered_map<std::string, CSoundBuffer*> m_ResourceBGM;			//! データ
	CSoundManager(void);
	~CSoundManager(void);
public:
	static CSoundManager* GetSound(void);									//! マネージャー呼び出し 
	static CSound* GetSoundSE(const std::string& str);						//! 再生可能なサウンド取得
	static CSoundBuffer* GetSoundBGM(const std::string& str);				//! 再生可能なサウンド取得
	static CSoundBuffer* GetSoundBuffer(const std::string& str);			//! 再生可能なサウンド取得
	static void PlaySE(const std::string& str);								//! 再生
	static void PlayBGM(const std::string& str);							//! 再生
	static void SetVolumeSE(const std::string& str, const float& vol);		//! 音量の調節 vol(0.0f ~ 1.0f)
	static void SetVolumeBGM(const std::string& str, const float& vol);		//! 音量の調節 vol(0.0f ~ 1.0f)
	static bool LoadSE(const std::string& str);								//! 読込
	static bool LoadBGM(const std::string& str);							//! 読込
	static void Update(void);												//! サウンド制御
	static void Release(void);												//! 解放

	static void StopBGM(void);
};

