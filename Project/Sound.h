#pragma once
#include	"Mof.h"

//サウンドエフェクト用クラス
class CSound
{
private:
	CSoundBuffer*	m_pSound;						//! サウンド
	bool			m_bPlay;						//! 再生フラグ
public:
	CSound(void);									//! コンストラクタ
	~CSound(void);									//! デストラクタ
	CSoundBuffer*	GetSoundBuffer(void);			//! サウンド取得
	bool			IsPlay(void) const;				//! 再生フラグ取得
	void			Play(void);						//! 再生
	bool			Load(const std::string& str);	//! 読込
	void			Update(void);					//! 更新
	void			Release(void);					//! 解放
};

