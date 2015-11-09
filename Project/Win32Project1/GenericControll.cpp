#include "GenericControll.h"
#include "Character.h"
#include "Player.h"

template<typename T>
void GenericControll<T>::init()
{
	objects.clear();
	for (auto itr = objects.begin(); objects.end() != itr;)
	{
		if (typeid(*itr) == typeid(Player))
		{
			delete (*itr);
			itr = objects.erase(itr);
			continue;
		}
		++itr;
	}

}

template<typename T>
bool GenericControll<T>::update()
{
	if (isFinished()) return true;
	for (T* object : objects)
	{
		updateOne(object);
	}
	create();
	hit();
	remove();
	return false;
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
	for (auto itr = objects.begin(); objects.end() != itr;)
	{
		if (isDead(*itr))
		{
			delete (*itr);
			itr = objects.erase(itr);
			continue;
		}
		++itr;
	}

}

template class GenericControll<Character>;