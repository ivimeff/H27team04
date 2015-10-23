#include "GenericControll.h"
#include "Character.h"

template<typename T>
void GenericControll<T>::init()
{
	objects.clear();
}

template<typename T>
void GenericControll<T>::update()
{
	for (T* object : objects)
	{
		updateOne(object);
	}
	create();
	hit();
	remove();
}

template<typename T>
void GenericControll<T>::draw()
{
	for (T* object : objects)
	{
		drawOne(object);
	}
}



template<typename T>
void GenericControll<T>::add(T* _object)
{
	initOne(_object);
	objects.push_back(_object);
}

template<typename T>
void GenericControll<T>::addObj(T* _object)
{
	newObjects.push_back(_object);
}

template<typename T>
void GenericControll<T>::create()
{
	for (T* object : newObjects)
	{
		add(object);
	}
	newObjects.clear();
}

template<typename T>
void GenericControll<T>::remove()
{
	deleteObjects.clear();
	for (T* object : objects)
	{
		if (isDead(object))
			deleteObjects.push_back(object);
	}

	for (T* object : deleteObjects)
	{
		removeOne(object);
	}

}

template class GenericControll<Character>;