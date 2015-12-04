#ifndef _GENERIC_CONTROLL_
#define _GENERIC_CONTROLL_

#include <vector>
#include "IGenericMediator.h"

template<typename T> class GenericControll : public IGenericMediator<T>
{
public:
	virtual ~GenericControll();
	virtual void init();
	bool update();
	void draw();
	virtual void addObj(T* _object);
protected:
	std::vector<T*> objects;
	void add(T* _object);
	virtual void hit() = 0;
	virtual void initOne(T* _object) = 0;
	virtual void updateOne(T* _object) = 0;
	virtual void drawOne(T* _object) = 0;
	virtual bool isDead(T* _object) = 0;
	virtual void removeOne(T* _object) = 0;
	virtual bool isFinished() = 0;
private:
	std::vector<T*> newObjects;
	std::vector<T*> deleteObjects;
	void create();
	void remove();
};

#endif