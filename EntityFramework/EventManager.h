#pragma once
#include "Bag.h"
#include "System.h"
#include <functional>
 
namespace ef
{

class BaseEvent;
 

class EventManager
{
private:
	template <class E>
	class EventCallBack
	{
	private:
		std::function<void(E &)> callBack;
	public:
		EventCallBack(std::function<void(E &)> func);
		void operator()(BaseEvent & e);
	};

	Bag<Bag<std::function<void(BaseEvent &)>>> callBacks;
public:
	EventManager();
	~EventManager();

	template <class E, class S>
	void listenTo(S * system, void (S::*callBack) (E &) );
	
	template <class E> 
	void emit(E & event);
};

template <class E>
EventManager::EventCallBack<E>::EventCallBack(std::function<void(E &)> func):callBack(func)
{
}

template <class E>
void EventManager::EventCallBack<E>::operator()(BaseEvent & e)
{
	callBack(static_cast<E&>(e));
}

template <class E, class S>
void EventManager::listenTo(S * system, void (S::* callBack) (E &))
{
	std::function<void(E &)> func=std::bind(callBack, system, std::placeholders::_1);
	callBacks.ensureSize(E::getIndex()+1);
	callBacks[E::getIndex()].add(EventCallBack<E>(func));
	
}

template <class E>
void EventManager::emit(E & event)
{
	for(std::size_t i=0; i<callBacks[E::getIndex()].size(); ++i)
		callBacks[E::getIndex()][i].operator()(event);
}

}