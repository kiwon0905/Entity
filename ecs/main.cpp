#include <iostream>
#include "Component.h"
#include "Event.h"
#include "System.h"


#include "Entity.h"
#include "EntityManager.h"
#include "World.h"

#include "vld.h"

#include <functional>

class Velocity : public Component<Velocity>
{
public:
	Velocity(int x, int y)
	{this->x=x; this->y=y;}
	int x; 
	int y;
};

class Position : public Component<Position>
{
public: 
	Position(int x, int y)
	{this->x=x; this->y=y;}
	int x;
	int y;
};

class TVEvent : public Event<TVEvent>
{
public:
	Entity * theEntity;
	TVEvent(Entity * e){theEntity=e;}
};


class KinematicSystem : public System<KinematicSystem>
{
public:
	void init(EventManager & em)
	{
		System::init(em);
		em.listenTo<TVEvent, KinematicSystem>(this, &KinematicSystem::receive);
	}

	bool isInterested(Entity * e)
	{
		return e->hasComponent<Velocity>() && e->hasComponent<Position>();
	}

	void receive(TVEvent & event)
	{
		std::cout<<"TVEVENT RECEIVED!\n";
	}

	void processEntity(Entity * e, EventManager & em, double dt)
	{
		e->getComponent<Position>()->x+=e->getComponent<Velocity>()->x;
		e->getComponent<Position>()->y+=e->getComponent<Velocity>()->x;
		if(e->getComponent<Position>()->x>3)
			em.emit(TVEvent(e));

	}   
};

void printInfo(Entity * e);

int main()
{
	std::cout<<std::boolalpha;
	World world;
	world.addSystem(new KinematicSystem);
	world.init();
	
	Entity * e=world.createEntity();
	
	e->addComponent(new Velocity(1, 1));
	e->addComponent(new Position(0, 0));
	e->addToWorld();

	for(int i=0; i<5; ++i)
	{
		printInfo(e);
		world.step(1);
	}
	


	std::cin.get();
}


void printInfo(Entity * e)
{
	if(e->hasComponent<Velocity>() && e->hasComponent<Position>())
	std::cout<<"("<<e->getComponent<Position>()->x<<", "<<e->getComponent<Position>()->y<<")\n";
}