#include "EmptyGameObject.h"

using namespace baseclass;

EmptyGameObject::EmptyGameObject(std::string strName) : GameObject(strName) {}

EmptyGameObject::~EmptyGameObject() {}

void EmptyGameObject::Initialize() {}