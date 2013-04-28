#pragma once
#include "Bag.h"

#include "System.h"

class EventManager
{
private:
	Bag<Bag<BaseSystem *>> systems;
public:
	EventManager();
	~EventManager();

	template <class T>
	void listenTo(BaseSystem * system);
	
	template <class T> 
	void emit(T & event);
};

template <class T>
void EventManager::listenTo(BaseSystem * system)
{
	systems.ensureSize(T::getIndex()+1);
	systems[T::getIndex()].add(system);
}

template <class T>
void EventManager::emit(T & event)
{
	for(std::size_t i=0; i<systems[T::getIndex()].size(); ++i)
		systems[T::getIndex()][i]->receive(event);
}

