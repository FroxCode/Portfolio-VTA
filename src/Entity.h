#pragma once
#include "Component.h"
#include "SDL.h"
#include <vector>

class Entity
{
	
private:
	std::vector<Component*> components;
	std::string m_tag;
public:
	Entity() {}
	Entity(std::string tag) { m_tag = tag; }
	~Entity() { components.clear(); }

	void addComponent(Component *comp) { components.push_back(comp); }
	std::vector<Component*> getComponents() { return components; }

	void setTag(std::string tag) { m_tag = tag; }
	std::string getTag() { return m_tag; }
};