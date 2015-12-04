#ifndef _I_GENERIC_MEDIATOR_
#define _I_GENERIC_MEDIATOR_

template<typename T>
class IGenericMediator
{
public:
	virtual void addObj(T* _object) = 0;
};

#endif