#include		"MoveObject.h"

CMoveObject::CMoveObject() : CEmpty() {


}

CMoveObject::~CMoveObject() {


}

void CMoveObject::Initialize() {


}

bool CMoveObject::Load() {

	RectLoad("RectTree.txt");
	return true;

}

void CMoveObject::Update(const bool& me) {

}