#pragma once
#include <cstddef>

class BaseComponent 
{
protected:
	static std::size_t counter;
public:
	BaseComponent(){}
	virtual ~BaseComponent(){}
};

template <class T>
class Component : public BaseComponent
{
public:
	Component(){}
	virtual ~Component(){}
	static std::size_t getIndex();
};

template <class T>
std::size_t Component<T>::getIndex()
{
	static std::size_t index=counter++;
	return index;
}
