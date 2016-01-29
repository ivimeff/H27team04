#include "GenericControll.h"
#include "Character.h"
#include "Player.h"

template<typename T>
GenericControll<T>::~GenericControll()
{
	for (auto itr = objects.begin(); objects.end() != itr;)
	{
		delete (*itr);
		itr = objects.erase(itr);
		continue;
	}

}

template<typename T>
void GenericControll<T>::init()
{
	objects.clear();
	for (auto itr = objects.begin(); objects.end() != itr;)
	{
		//if (typeid(*itr) == typeid(Player))
		//{
			delete (*itr);
			itr = objects.erase(itr);
			continue;
		//}
		++itr;
	}

}

template<typename T>
void GenericControll<T>::firstUpdate()
{

}

template<typename T>
bool GenericControll<T>::update()
{
	if (isFinished()) return true;
	firstUpdate();
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
void GenericControll<T>::firstDraw()
{

}

template<typename T>
void GenericControll<T>::draw()
{
	firstDraw();
	for (T* object : objects)
	{
		drawOne(object);
	}
}

template<typename T>
void GenericControll<T>::hit()
{

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

template<typename T>
bool GenericControll<T>::isFinished()
{
	return false;
}

template class GenericControll<Effect>;
template class GenericControll<Character>;