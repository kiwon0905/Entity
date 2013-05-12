#pragma once
#include <cstddef>

namespace ef
{

class Entity;

class BaseEvent
{
protected:
	static std::size_t counter;
public:
	BaseEvent(){}
	virtual ~BaseEvent(){}
};

template <class T>
class Event : public BaseEvent
{
public:
	Event(){}
	virtual ~Event(){}
	static std::size_t getIndex();
};

template <class T>
std::size_t  Event<T>::getIndex()
{
	static std::size_t index=counter++;
	return index;
}


class EntityAddedEvent : public Event<EntityAddedEvent>
{
public:
	Entity * e;
	EntityAddedEvent(Entity * e);
};

class EntityRemovedEvent : public Event<EntityRemovedEvent>
{
public:
	Entity * e;
	EntityRemovedEvent(Entity * e);
};

class EntityChangedEvent : public Event<EntityChangedEvent>
{
public:
	Entity * e;
	EntityChangedEvent(Entity * e);
};

}
