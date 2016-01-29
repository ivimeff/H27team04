#include "EffectManager.h"

EffectManager::EffectManager()
{

}

EffectManager::~EffectManager()
{

}

void EffectManager::initOne(Effect* _object)
{
	_object->init();
}

void EffectManager::updateOne(Effect* _object)
{
	_object->update();
}

void EffectManager::drawOne(Effect* _object)
{
	_object->draw();
}

bool EffectManager::isDead(Effect* _object)
{
	return _object->isDead();
}

void EffectManager::addObj(Effect* _object)
{
	GenericControll<Effect>::addObj(_object);
}