#include <iostream>

#include "EntityFramework.h"

#include <VisualLeakDetector/vld.h>

using namespace ef;     


struct TurnedZombieEvent : public Event<TurnedZombieEvent> {};

struct ZombieThrewUpEvent : public Event<ZombieThrewUpEvent>{};

struct ZombieComponent : public Component<ZombieComponent>
{
	int health;
	ZombieComponent(int h):health(h){}
};

struct HumanComponent : public Component<HumanComponent>
{
	int health;
	HumanComponent(int h):health(h){}
};

class ZombieSystem : public System<ZombieSystem>
{
	bool isInterested(Entity * e)
	{
		return e->hasComponent<ZombieComponent>();
	}

	void processEntity(Entity * e, EventManager & em, double dt)
	{
		std::cout<<"A zombie processed\n";
		Entity * e2=getWorld().createEntity();
		e2->addComponent(new ZombieComponent(0));
		e2->addToWorld();
	}
};

class HumanSystem : public System<HumanSystem>
{
	bool isInterested(Entity * e)
	{
		return e->hasComponent<HumanComponent>();
	}

	void processEntity(Entity * e, EventManager & em, double dt)
	{
		std::cout<<"A human processed\n";
		Entity * e2=getWorld().createEntity();
		e2->addComponent(new HumanComponent(0));
		e2->addToWorld();

	}
};


int main()
{
	std::cout<<std::boolalpha;
	World world;
	world.addSystem(new ZombieSystem);
	world.addSystem(new HumanSystem);
	world.init();

	Entity * e=world.createEntity();
	e->addComponent(new HumanComponent(5));
	e->addToWorld();

	Entity * e2=world.createEntity();
	e2->addComponent(new ZombieComponent(4));
	e2->addToWorld();
	
	for(int i=0; i<2; i++)
	{
		world.getSystem<HumanSystem>().step(0);
		world.getSystem<ZombieSystem>().step(0);
	}
	std::cin.get();
}
