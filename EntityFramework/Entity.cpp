#include "Entity.h"
#include "Ecs.h"

Entity::Entity(Entity::Id id) :m_id(id)
{
	m_components.resize(MAX_COMPONENTS);
}


Entity::~Entity()
{
}


void Entity::removeAllComponents()
{
	for (auto & c : m_components)
		c.reset(nullptr);
}

Entity::Id Entity::getId()
{
	return m_id;
}

void Entity::setId(Entity::Id id)
{
	m_id = id;
}