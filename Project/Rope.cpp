#include "Rope.h"



CRope::CRope()
{
	Initialize();
	Load();
}


CRope::~CRope()
{
}

void CRope::Initialize(void)
{

}

bool CRope::Load(void)
{
	RectLoad("RectRope.txt");
	return true;
}

void CRope::Update(const bool& me)
{

}
