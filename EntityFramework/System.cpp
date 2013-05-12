#include "System.h"
#include "EventManager.h"
#include "Event.h"

namespace ef
{

std::size_t BaseSystem::counter=0;

BaseSystem::BaseSystem(): world(nullptr)
{
}

BaseSystem::~BaseSystem()
{
}

void BaseSystem::init(EventManager & em)
{
	em.listenTo<EntityAddedEvent>(this, &BaseSystem::receive);
	em.listenTo<EntityChangedEvent>(this, &BaseSystem::receive);
	em.listenTo<EntityRemovedEvent>(this, &BaseSystem::receive);
}

void BaseSystem::setWorld(World * world)
{
	this->world=world;
}

void BaseSystem::addEntity(Entity * e)
{
	activeEntities.add(e);
}

void BaseSystem::removeEntity(Entity * e)
{
	//remove by value
		for(std::size_t i=0; i<activeEntities.size(); ++i)
		{
			if(activeEntities[i]==e)
			{
				activeEntities.remove(i);
				break;
			}
		}
}

bool BaseSystem::hasEntity(Entity * e)
{
	return entityTable.count(e)==1;
}

void BaseSystem::update(EventManager & em, double dt)
{
	for(std::size_t i=0; i<added.size(); ++i)
		addEntity(added[i]);

	//!Order is important
	for(std::size_t i=0; i<removed.size(); ++i)
		removeEntity(removed[i]);

	added.clear();
	removed.clear();

	for(std::size_t i=0; i<activeEntities.size(); ++i)
		processEntity(activeEntities[i], em, dt);

}

void BaseSystem::receive(EntityAddedEvent & e)
{
	if(isInterested(e.e))
	{
		added.add(e.e);
		entityTable.insert(e.e);
	}
}

void BaseSystem::receive(EntityChangedEvent & e)
{
	if(hasEntity(e.e) && !isInterested(e.e))
	{
		removed.add(e.e);
		entityTable.erase(e.e);
	}
	else if( !(hasEntity(e.e)) && isInterested(e.e))
	{
		added.add(e.e);
		entityTable.insert(e.e);
	}
}

void BaseSystem::receive(EntityRemovedEvent & e)
{
	if(hasEntity(e.e))
	{
		removed.add(e.e);
		entityTable.erase(e.e);
	}
}

World * BaseSystem::getWorld()
{
	return world;
}


}