#pragma once
#ifndef ENUM_COMPONENT_TYPE_H
#define ENUM_COMPONENT_TYPE_H

enum ComponentType : int
{
	NONE = -1,
	RENDERER = 0,
	INPUT,
	SCRIPT,
	PHYSICS
};

#endif // !ENUM_COMPONENT_TYPE_H