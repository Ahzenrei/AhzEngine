#include "SceneElement.h"

void AddComponent(Component component) noexcept
{
	components.insert(component.GetComponentType(), component);
}