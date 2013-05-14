#pragma once
#include "EntityManager.h"
#include "EventManager.h"
#include "Bag.h"
  
namespace ef
{

class World
{
	friend class Entity;
	friend class BaseSystem;
private:
	EntityManager entityManager;
	EventManager eventManager;
	Bag<BaseSystem *> systems;

	void addEntity(Entity * e);
	void removeEntity(Entity * e);
public:
	World();
	~World();

	void init();

	Entity * createEntity();

	template <class S>
	void addSystem(S * newSystem);

	template <class T>
	T & getSystem();
};

template <class S>
void World::addSystem(S * newSystem)
{
	systems.ensureSize(S::getIndex()+1);
	systems[S::getIndex()]=newSystem;
	newSystem->setWorld(this);
}

template <class T>
T & World::getSystem()
{
	return static_cast<T&>(*systems[T::getIndex()]);
}

}