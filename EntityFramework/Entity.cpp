#include "Entity.h"
#include "World.h"
#include "Component.h"
#include "Event.h"

namespace ef
{

Entity::Entity(std::size_t id_, World * world_):id(id_), world(world_) 
{
}

Entity::~Entity()
{
	for(std::size_t i=0; i<components.size(); ++i)
	{
		delete components[i];
	}
}

std::size_t Entity::getID()
{
	return id;
}

bool Entity::isActive()
{
	return world->entityManager.isActive(this);
}

void Entity::removeAllComponents()
{
	for(std::size_t i=0; i<components.size(); ++i)
	{
		delete components[i];
		components[i]=nullptr;			
	}
	if(isActive())
		world->eventManager.emit(EntityChangedEvent(this));
}

void Entity::addToWorld()
{
	world->addEntity(this);
	world->eventManager.emit(EntityAddedEvent(this));
}

void Entity::removeFromWorld()
{
	world->removeEntity(this);
	world->eventManager.emit(EntityRemovedEvent(this));
}

}