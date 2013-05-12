#include "World.h"
namespace ef
{


World::World():entityManager(this)
{
}


World::~World()
{
		//delete all the systems
	for(std::size_t i=0; i<systems.size(); ++i)
		delete systems[i];
}

Entity * World::createEntity()
{
	return entityManager.create();
}

void World::addEntity(Entity * e)
{
	entityManager.add(e);
}

void World::removeEntity(Entity * e)
{
	entityManager.remove(e);
}

void World::init()
{
	for(std::size_t i=0; i<systems.size(); ++i)
		systems[i]->init(eventManager);
}

void World::addSystem(BaseSystem * newSystem)
{
	systems.add(newSystem);
	newSystem->setWorld(this);
}

void World::step(double dt)
{
	for(std::size_t i=0; i<systems.size(); ++i)
		systems[i]->update(eventManager, dt);
}

}