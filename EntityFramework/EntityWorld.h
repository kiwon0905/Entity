#pragma once
#include <vector>
#include <unordered_map>
#include <memory>
#include "System.h"
#include "Entity.h"

class EntityWorld
{
public:		
	Entity * create();
	void addEntity(Entity * e);
	void removeEntity(Entity * e);
	void refreshEntity(Entity * e);

	template <class S, class ... Args>
	void addSystem(Args && ...args);

	void update(float dt);
private:	
	class IDPool
	{
	private:
		std::vector<Entity::Id> pool;
		Entity::Id nextId = 0;
	public:
		Entity::Id checkOut();
		void checkIn(Entity::Id id);
	} m_idPool;
	enum Change{Add, Remove, Refresh};

	std::vector<std::pair<Change, Entity*>> m_changes;
	std::vector<std::unique_ptr<System>> m_systems;
	std::vector<std::unique_ptr<Entity>> m_entities;

};

template <class S, class ... Args>
void EntityWorld::addSystem(Args && ...args)
{
	m_systems.push_back(std::make_unique<S>(std::forward<Args>(args)...));
}

