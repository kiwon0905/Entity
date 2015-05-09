#pragma once
#include <vector>

class Entity;

class System
{
public:
	friend class EntityWorld;

	System();
	virtual ~System();

	virtual bool isInterested(Entity * e) = 0;
	virtual void update(EntityWorld & w, float dt) = 0;
	std::vector<Entity *> getEntities();
private:	
	bool hasEntity(Entity * e);

	void refreshEntity(Entity * e);
	void removeEntity(Entity * e);
	void addEntity(Entity * e);

	std::vector<Entity*> m_entities;

};

