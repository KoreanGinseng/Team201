#include "ObjTree.h"



CObjTree::CObjTree()
{
	Initialize();
	Load();
}


CObjTree::~CObjTree()
{
}

void CObjTree::Initialize(void)
{
}

bool CObjTree::Load(void)
{
	RectLoad("RectTree.txt");
	return true;
}

void CObjTree::Update(const bool & me)
{
}
