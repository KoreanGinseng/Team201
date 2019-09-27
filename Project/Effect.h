#pragma once
#include "Mof.h"
class Effect
{
	enum tag_EFFECTTTYPE {
		EFC_01,		//âºê›íË
		EFC_02,		//âºê›íË

		EFC_TYPECOUNT,
	};
	private:
		float m_Posx;
		float m_Posy;
		float m_bshow;
public:
	Effect();
	~Effect();
	void Initialize(int type);
	void Update(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};

