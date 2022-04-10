#pragma once


class Component
{
public:
	enum class ComponentType {Default, Mesh};

	virtual ComponentType GetComponentType() const ;
};

