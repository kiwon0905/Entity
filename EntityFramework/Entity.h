#pragma once
#include <cstddef>
#include "Bag.h"

namespace ef
{

class BaseComponent;
class Entity
{
	friend class World;
private:
	std::size_t id;
	World * world;
	Bag<BaseComponent *> components;
public:
	Entity(std::size_t id, World * world);
	~Entity();

	std::size_t getID();
	
	template <class T>
	bool hasComponent();

	template <class T>
	T * getComponent();

	template <class T>
	void removeComponent();

	void removeAllComponents();

	template <class T>
	void addComponent(T * newComponent);

	void addToWorld();

	void removeFromWorld();

	bool isActive();

};

template <class T>
bool Entity::hasComponent()
{
	return getComponent<T>()!=nullptr;
}

template <class T>
T * Entity::getComponent()
{
	if(components.size()<T::getIndex()+1)
		return nullptr;
	return static_cast<T*>(components[T::getIndex()]);
}

template <class T>
void Entity::removeComponent()
{
	if(!(components.size()<T::getIndex()+1))
	{
		delete components[T::getIndex()];
		components[T::getIndex()]=nullptr;
	}
	if(isActive())
		world->eventManager.emit(EntityChangedEvent(this));

}

template <class T>
void Entity::addComponent(T * newComponent)
{
	components.ensureSize(T::getIndex()+1);	
	//if entity already has this component, it deletes it first
	delete components[T::getIndex()];
	components[T::getIndex()]=newComponent;

	if(isActive())
		world->eventManager.emit(EntityChangedEvent(this));
}

}