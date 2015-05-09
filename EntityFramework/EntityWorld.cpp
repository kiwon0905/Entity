#include "EntityWorld.h"

void EntityWorld::IDPool::checkIn(std::size_t id)
{
	pool.push_back(id);
}

Entity::Id EntityWorld::IDPool::checkOut()
{
	if (pool.size() > 0)
	{
		Entity::Id id = pool.back();
		pool.pop_back();
		return id;
	}
	return nextId++;
}

Entity * EntityWorld::create()
{
	Entity::Id id = m_idPool.checkOut();
	if (m_entities.size() < id + 1)
		m_entities.resize(id + 1);
	m_entities[id].reset(new Entity(id));

	return m_entities[id].get();
}

void EntityWorld::update(float dt)
{
	for (auto & c : m_changes)
	{
		switch (c.first)
		{
		case Add:
			for (auto & s : m_systems)
				s->addEntity(c.second);
			break;
		case Remove:
			for (auto & s : m_systems)
			{
				s->removeEntity(c.second);
				c.second->removeAllComponents();
			}	
			m_idPool.checkIn(c.second->getId());
			break;
		case Refresh:
			for (auto & s : m_systems)
				s->refreshEntity(c.second);
			break;
		}
	}
	m_changes.clear();
	for (auto & system : m_systems)
		system->update(*this, dt);
}

void EntityWorld::addEntity(Entity * e)
{
	m_changes.emplace_back(Add, e);
}

void EntityWorld::removeEntity(Entity * e)
{
	m_changes.emplace_back(Remove, e);
}

void EntityWorld::refreshEntity(Entity * e)
{
	m_changes.emplace_back(Refresh, e);
}
