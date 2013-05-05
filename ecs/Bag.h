#pragma once
#include <vector>
#include <utility>

template <class T>
class Bag
{
private:
	std::vector<T> vec;
public:
	Bag();
	~Bag();

	/// \brief Gets an element by its index. 
	/// Doesn't check if index is out of bound
	/// @param i Index 
	/// @return The element at that position
	T & operator[](int i);

	/// @param t Element to add
	void add(T t);

	/// \brief Removes an element by its index. 
	/// Removes an element by using swap-and-pop technique
	/// Doesn't check if the index is out of bound
	/// @param i Index for the element to remove
	/// @return The element that was removed
	T remove(int i);

	/// \brief Removes the last element
	/// Doesn't check if there are no elements
	/// @return The element that was removed(The last element)
	T removeLast();

	/// \brief Clears all the elements
	/// Doesn't free the memory
	void clear();

	/// \brief Ensures the size of the bag
	/// Increases the size of the bag if current size is smaller than requested.
	/// Otherwise no-op
	/// @param i size 
	void ensureSize(std::size_t i);

	/// \brief Returns the size of the bag
	/// @return The size of the bag
	std::size_t size() const;

	/// \brief Check if the bag is empty
	/// size()==0
	/// @return true if the bag is empty
	bool isEmpty() const;
};

///@}

template <class T>
Bag<T>::Bag()
{
}

template <class T>
Bag<T>::~Bag()
{
}
 
template <class T>
T & Bag<T>::operator[](int i)
{
	return vec[i];
}

template <class T>
void Bag<T>::add(T  t)
{
	vec.push_back(t);
}


template <class T>
T Bag<T>::remove(int i)
{
	T t=vec[i];
	std::swap(vec[i], vec[vec.size()-1]);
	vec.pop_back();
	return t;
}

template <class T>
T Bag<T>::removeLast()
{
	T t=vec[vec.size()-1];
	vec.pop_back();
	return t;
}

template <class T>
void Bag<T>::ensureSize(unsigned int i)
{
	//resize only if current size is smaller than requested size
	if(vec.size()<i)
		vec.resize(i);
}


template <class T>
std::size_t Bag<T>::size() const
{
	return vec.size();
}

template <class T>
void Bag<T>::clear()
{
	vec.clear();
}


