#pragma once
#include <cstddef>

class BaseComponent
{
protected:
	friend class Entity;
	static std::size_t counter;
public:
	virtual ~BaseComponent() = default;
};

template <class T>
class Component : public BaseComponent
{
public:
	virtual ~Component() = default;
	static std::size_t getIndex();
};

template <class T>
std::size_t Component<T>::getIndex()
{
	static std::size_t index = counter++;
	return index;
}