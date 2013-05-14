#pragma once
#include <cstddef>
#include <unordered_set>
#include "Bag.h"

namespace ef
{

class Entity;
class EventManager;
class EntityRemovedEvent;
class EntityChangedEvent;
class EntityAddedEvent;

class BaseSystem
{
	friend class World;
private:
	World * world;
	Bag<Entity *> added;
	Bag<Entity *> removed;
	Bag<Entity *> activeEntities;

	std::unordered_set<Entity *> entityTable;

	bool hasEntity(Entity * e);
	void setWorld(World * world);

	void addEntity(Entity * e);
	void removeEntity(Entity * e);

	virtual bool isInterested(Entity * e)=0;
	
	virtual void processEntity(Entity * e, EventManager & em, double dt)=0;
protected:	
	virtual void receive(EntityAddedEvent & e);
	virtual void receive(EntityChangedEvent & e);
	virtual void receive(EntityRemovedEvent & e);
	static std::size_t counter;
public:
	BaseSystem();
	virtual ~BaseSystem();

	virtual void init(EventManager & em);
	void step(double dt);

	World & getWorld();
};

template <class T>
class System : public BaseSystem
{
public:
	System(){}
	~System(){}
	static std::size_t getIndex();
};

template <class T>
std::size_t System<T>::getIndex()
{
	static std::size_t index=counter++;
	return index;
}

}