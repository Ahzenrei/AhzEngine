#include "SceneElement.h"

void SceneElement::AddComponent(Component * component) noexcept
{
	components.insert({ component->GetComponentType(), component });
}

bool SceneElement::HasComponent(Component::ComponentType type) const noexcept
{
	return components.find(type) != components.end();
}

Component* SceneElement::GetComponent(Component::ComponentType type) noexcept
{
	auto elementFound = components.find(type);
	return elementFound != components.end() ? elementFound->second : nullptr;
}
