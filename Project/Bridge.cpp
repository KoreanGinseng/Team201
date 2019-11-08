#include "Bridge.h"



CBridge::CBridge()
{
	Initialize();
	Load();
}


CBridge::~CBridge()
{
}

void CBridge::Initialize(void)
{
}

bool CBridge::Load(void)
{
	RectLoad("RectBridge.txt");
	return true;
}

void CBridge::Update(const bool & me)
{
}
