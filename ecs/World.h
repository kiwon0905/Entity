#pragma once
#include "EntityManager.h"
#include "EventManager.h"
#include "Bag.h"


class BaseSystem;

class World
{
	friend class Entity;
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
	void addSystem(BaseSystem * newSystem);
	Entity * createEntity();
	void step(double dt);
};

