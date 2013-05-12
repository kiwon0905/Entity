#include "EntityManager.h"
#include "Entity.h"

namespace ef
{

EntityManager::IDPool::IDPool():nextAvailableID(0)
{
}

EntityManager::IDPool::~IDPool()
{
}

void EntityManager::IDPool::checkIn(std::size_t n)
{
	pool.add(n);
}

std::size_t EntityManager::IDPool::checkOut()
{
	if(pool.size() > 0)
		return pool.removeLast();
	return nextAvailableID++;
}

bool EntityManager::EntityPtrComparator::operator()(Entity * e1, Entity * e2)
{
	return e1->getID() > e2->getID();
}

EntityManager::EntityManager(World * world_): world(world_)
{
}

EntityManager::~EntityManager()
{
	for(std::size_t i=0; i<activeEntities.size(); ++i)
		delete activeEntities[i];
	for(std::size_t i=0; i<removedEntities.size(); ++i)
		delete removedEntities[i];
	for(Entity * e : inactiveEntities)
		delete e;
}

Entity * EntityManager::create()
{
	//check the recycle bin
	Entity * e=nullptr;
	if(removedEntities.size()>0)
		e=removedEntities. removeLast();
	else
	{
		e=new Entity(idPool.checkOut(), world);
		inactiveEntities.insert(e);
	}
	return e;
}

bool EntityManager::isActive(Entity * e)
{
	if(e->getID()+1 > activeEntities.size())
		return false;
	return activeEntities[e->getID()]!=nullptr;
}

void EntityManager::add(Entity * e)
{
	inactiveEntities.erase(e);
	activeEntities.ensureSize(e->getID()+1);
	activeEntities[e->getID()]=e;
}

void EntityManager::remove(Entity * e)
{
	activeEntities[e->getID()]=nullptr;
	e->removeAllComponents();
	removedEntities.add(e);
}

}