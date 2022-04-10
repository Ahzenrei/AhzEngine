#include "SceneElement.h"

void SceneElement::AddComponent(Component * component) 
{
	components.insert({ component->GetComponentType(), component });
}

bool SceneElement::HasComponent(Component::ComponentType type) const 
{
	return components.find(type) != components.end();
}

Component* SceneElement::GetComponent(Component::ComponentType type) 
{
	auto elementFound = components.find(type);
	return elementFound != components.end() ? elementFound->second : nullptr;
}
