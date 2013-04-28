#include <iostream>
#include "Component.h"
#include "Event.h"
#include "System.h"


#include "Entity.h"
#include "EntityManager.h"
#include "World.h"

#include "vld.h"

class A : public Component<A>
{
private:
	int a;
public: 
	A(int a_):a(a_){}
	~A(){}
	void say(){std::cout<<"I'm a-"<<a<<"\n";}
};

class B: public Component<B>
{
private:
	int b;
public:
	B(int b_):b(b_){}
	~B(){}
	void say(){std::cout<<"I'm B-"<<b<<"\n";}
};

class ASystem :public System<ASystem>
{
private:
	bool isInterested(Entity * e)
	{
		return (e->hasComponent<A>());
	}
public:
	void processEntity(Entity * e, EventManager & em, double dt)
	{
		e->getComponent<A>()->say();
		e->removeComponent<A>();
		e->addComponent(new B(1));

	}

	void init(EventManager & em){System::init(em);}

};

class BSystem : public System<BSystem>
{
private:
	bool isInterested(Entity * e)
	{
		return (e->hasComponent<B>());
	}
public:

	void processEntity(Entity * e, EventManager & em, double dt)
	{
		e->getComponent<B>()->say();
	}
	void init(EventManager & em)
	{
		System::init(em);
	}
};


int main()
{
	std::cout<<std::boolalpha;
	World world;
	world.addSystem(new ASystem);
	world.addSystem(new BSystem);
	world.init();
	
	Entity * e=world.createEntity();
	
	e->addToWorld();
		e->addComponent(new A(0));
		//e->removeComponent<B>();
	world.step(0);
	world.step(0);world.step(0);world.step(0);
	


	std::cin.get();
}