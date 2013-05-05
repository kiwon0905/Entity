#pragma once
#include <cstddef>
#include <unordered_set>
#include "Bag.h"
#include "Event.h"

class Entity;
class EventManager;

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
	void process(EventManager & em, double dt);

	virtual bool isInterested(Entity * e)=0;
protected:
	static std::size_t counter;
public:
	BaseSystem();
	virtual ~BaseSystem();

	World * getWorld();

	virtual void receive(EntityAddedEvent & e);
	virtual void receive(EntityChangedEvent & e);
	virtual void receive(EntityRemovedEvent & e);

	virtual void init(EventManager & em);
	virtual void processEntity(Entity * e, EventManager & em, double dt)=0;

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