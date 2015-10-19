#ifndef _GENERIC_CONTROLL_
#define _GENERIC_CONTROLL_

#include <vector>

template<typename T> class GenericControll
{
public:
	virtual void init();
	void update();
	void draw();
	void add(T* _object);
	void addObj(T* _object);
protected:
	std::vector<T*> objects;
	virtual void hit() = 0;
	virtual void initOne(T* _object) = 0;
	virtual void updateOne(T* _object) = 0;
	virtual void drawOne(T* _object) = 0;
	virtual bool isDead(T* _object) = 0;
	virtual void removeOne(T* _object) = 0;
private:
	std::vector<T*> newObjects;
	std::vector<T*> deleteObjects;
	void create();
	void remove();
};

#endif