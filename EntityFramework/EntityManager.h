#pragma once
#include "Bag.h"
#include <set>

namespace ef
{

class World;
class Entity;

class EntityManager
{
private:
	class IDPool
	{
	private: 
		Bag<int> pool;
		std::size_t nextAvailableID;
	public:
		IDPool();
		~IDPool();
		std::size_t checkOut();
		void checkIn(std::size_t n);
	} idPool;
	World * world;
	struct EntityPtrComparator
	{
		bool operator()(Entity * e1, Entity *e2);
	};

	//Entities that haven't been added to the world
	std::set<Entity *, EntityPtrComparator> inactiveEntities;

	//Entities that have been removed from the world
	Bag<Entity *> removedEntities;

	//Entities that are active
	Bag<Entity *> activeEntities;


public:
	EntityManager(World * world);
	~EntityManager();

	bool isActive(Entity * e);
	Entity * create();
	void add(Entity * e);
	void remove(Entity * e);

};

}