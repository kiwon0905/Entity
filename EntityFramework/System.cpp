#include "System.h"


System::System()
{
}


System::~System()
{
}

std::vector<Entity*> System::getEntities()
{
	return m_entities;
}

void System::addEntity(Entity * e)
{
	if (isInterested(e))
		m_entities.push_back(e);
}

void System::refreshEntity(Entity * e)
{
	if (isInterested(e))
	{
		if (!hasEntity(e))
			m_entities.push_back(e);
	}
	else
		removeEntity(e);
}

void System::removeEntity(Entity * e)
{
	for (auto iter = m_entities.begin(); iter != m_entities.end(); ++iter)
	{
		if (*iter == e)
		{
			m_entities.erase(iter);
			break;
		}
	}
}

bool System::hasEntity(Entity * e)
{
	for (Entity * e2 : m_entities)
		if (e2 == e)
			return true;
	return false;
}