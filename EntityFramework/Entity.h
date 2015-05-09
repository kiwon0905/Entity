#pragma once
#include <vector>
#include <memory>
#include "Component.h"

class Entity
{
public:
	typedef std::size_t Id;
	Entity(Entity::Id id);
	~Entity();

	template <class T>
	bool hasComponent();

	template <class T>
	T * getComponent();

	template <class C, class ... Args>
	void addComponent(Args && ...args);

	template <class T>
	void removeComponent();

	void removeAllComponents();

	Entity::Id getId();
	void setId(Entity::Id id);
private:
	std::vector<std::unique_ptr<BaseComponent>> m_components;
	Entity::Id m_id;
};

template <class C>
bool Entity::hasComponent()
{
	return getComponent<C>()!=nullptr;
}

template <class C>
C * Entity::getComponent()
{
	return static_cast<C*>(m_components[C::getIndex()].get());
}

template <class C, class ... Args>
void Entity::addComponent(Args && ...args)
{
	m_components[C::getIndex()].reset(new C(std::forward<Args>(args)...));
}

template <class C>
void Entity::removeComponent()
{
	m_components[C::getIndex()].reset(nullptr);
}

